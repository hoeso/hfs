<?php
require_once("ParserCSV.php");
class LV extends ParserCSV
{
  private $a; // Vektor mit TopicToken-Treffern
  private $dim; // TopicToken-Dimension
  private $thema; // Das aktuelle Parse-Thema
  private $cZeile; // Zeilen Counter
  private $cFelder; // Anzahl Felder in der Zeile
  private $nFeld; // n.tes Feld in der Zeile
  private $z; // Felder der naechsten Zeile
  private $wZu; // Vektor mit Automaten-Schluesseln
  private $reihe; // Vektor mit einer Reihenfolge. Bedeutung abh. vom Wert in $this->thema
  function __construct($d, $thema=1, $czeile=0, $mode="r")
  {
    parent::__construct($d, $mode);
    $this->thema = $thema;
    unset($this->z);
    $this->cZeile = $czeile;
    $this->cFelder = 0;
    $this->nFeld = 0;
    if( false == parent::__get('lesbar') )
    {
      echo "<br>$d unlesbar ...<br>";
      return;
    }
    /*** Objekt rekonstruieren? ***/
    if( $this->cZeile ) // > 0 ? Dann auf diese Zeile positionieren
    { // Objekt wird nach Zustand Wechsel rekonstruiert
      $c = 1;
      while( false <> $this->z = $this->gibZeile )
      {
        ++$c;
        if( $c == $this->cZeile )
          break; // Bis hier wurde bereits geparst
      }
    }
    $this->a[0]=0;// hier Feld 0 rein = Token
    $this->a[1]=1;// hier Feld 1 rein = Gewicht
    $this->a[2]=2;// hier Feld 2 rein = Rang
    $this->a[3]=3;// hier Feld 3 rein = Topic
    $this->a[4]=4;// hier Feld 4 rein = TopicID
    $this->a[5]=5;// hier Feld 5 rein = Reihenfolge
    $this->a[6]=6;// hier Feld 6 rein = TokenID // wg. Pruefung auf [Token]SubToken
    $this->a[7]=7;// hier Feld 7 rein = TopicTokenID // Wert im Vektor $this->reihe wenn 1 == $this->thema wahr
    $this->dim = count($this->a);
    /*** where-Klausel mit Thema: WHERE $thema=tp.Rang ***/ 
    $sl = "SELECT t.Token, 0, tp.Rang, tp.Topic, tp.ID, 0, t.ID, tt.ID FROM TopicToken tt JOIN Topic tp ON (tt.TopicID=tp.ID) JOIN Token t ON (tt.TokenID=t.ID) WHERE $thema=tp.Rang ORDER BY Token DESC";
    DB::gibFelderArray( $sl, $this->a );

    /*** DESC, damit die Sub-Token chronologisch nach ihren Besitzern geprueft werden.
     *** erspart Code, weil nur nach Parent-Token gesucht werden braucht.
     *** Bei keiner Markierung dort kann selber markiert werden.
     ***/
    $this->wZu = array();
    $this->wZu[] = "anbietendKnopfZurueck";	 
    $this->wZu[] = "strukturierendLVTabelle";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'lesbar':
        return parent::__get('lesbar');
      case 'gibLaengeReihe':
        return count($this->reihe);
      case 'gibReihe':
        return $this->reihe;
      case 'gibZeile':
        return parent::__get('gibZeile');
      case 'gibZeilenZaehler':
        return $this->cZeile;
      case 'Thema':
        for( $i=0; $i < count($this->a); $i += $this->dim )
          if( $this->thema == $this->a[$i+2] ) // hier liegt die aktuelle Gewichtung
            return $this->thema;
        return 0;
      default:
        throw new Exception("LV hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function strukturieren()
  {
    /*** Struktur der Tabellenueberschrift lesen
     *** [0] Token [1] Gewicht [2] Thema [3] Topic [4] Topic.ID [5] gefunden-Stelle [6] Token.ID [7] TopicToken.ID
     ***/
    unset($this->reihe);
    $this->reihe = array();
    $z = array();
    for( $i=0; $i < count($this->a); $i += $this->dim )
      if( $this->a[$i+5] ) // hier liegt der gefunden-Zaehler
      {
        $iz = $this->a[$i+5] - 1; // gefunden-Zaehler beginnt bei 1, weil 0 == nicht gefunden
        $z[ $iz ] = $this->a[$i]; // Der Token
        $this->reihe[ $iz ] = $this->a[$i+7]; // Struktur abspeichern: Naechster Automat liest diese aus
      }
    for( $i=0; $i < count($z); $i++ )
      echo " | " . $z[$i];
    echo " |<br>Sind das die Spalten des LV?<br>";
    return true;
  }
  function gefunden()
  {
    /*** aktuelles Thema lesen
     *** [0] Token [1] Gewicht [2] Thema [3] Topic [4] Topic.ID [5] gefunden-Stelle [6] Token.ID [7] TopicToken.ID
     ***/
    $forderung = 0;
    $weight = 0;
    for( $i=0; $i < count($this->a); $i += $this->dim )
      if( $this->thema == $this->a[$i+2] ) // hier liegt die aktuelle Gewichtung
      {
        $weight += $this->a[$i+1]; // hier liegt das Gewicht des gefundenen Token
        if( !$forderung ) // gefordertes Gewicht noch nicht bekannt
          $forderung = DB::gibFeld( "SELECT Forderung FROM TopicForderung WHERE " . $this->a[$i+4] . "=TopicID" );
      }
    return !( $weight < $forderung ); // Mindestvorkommen erfuellt?
  }
  function finden()
  {
    /*** Token als einzelnes Wort: Gewichtung = 2.
     *** Token kommt in Wort vor: Gewichtung = 1.
     *** Fuer die einzelnen Topics eine Enitaet hinterlegen mit
     *** einer Mindestgewichtung, z.B. Ueberschrift : 2
     *** [0] Token [1] Gewicht [2] Thema [3] Topic [4] Topic.ID [5] gefunden-Stelle [6] Token.ID [7] TopicToken.ID
     ***/
/*** FF 2. Bei leerer Treffermenge mit aktuellem Thema in der Token-Liste verzweigen zum TopicTokenThema-Eintrag ***/
/*** $this->reihe[0] pruefen auf TopicTokenID und damit verzweigen zum TopicTokenThema-Eintrag ***/
    if( false == habWas( $this->a, 0, 7 ) )
    {
      echo "<br>nix gfundn<br>";
      $this->debug( "cF" );
      $this->debug();
      return false;
    }
    while( false <> $this->z = $this->gibZeile )
    {
      if( false == $this->z && !$this->cZeile )
        return false; // keine einzige Zeile bekommen, da stimmt was nicht
      $n = 1;
      $this->reset(); // loescht alle Token-Treffer
      ++$this->cZeile;
      $this->cFelder = count($this->z); // Anzahl Felder auslesen
      for ($c=0; $c < $this->cFelder; $c++)
      {
        unset($_s);
        $_s = explode( " ", utf8_encode($this->z[$c]) );
        for( $s=0; $s < count($_s); $s++ )
          for( $i=0; $i < count($this->a); $i += $this->dim )
            if( strstr( $_s[$s], $this->a[$i] ) ) // Token kommt vor
            {
              if( false == $this->parentTokenMarkiert( $this->a[$i+6] ) )
              {
                ++$this->a[$i+1]; // gefundenen Token markieren
                $this->a[$i+5] = $n; // das n.te gefundene Token
                ++$n;
              }
            }
      }
      if( $n > 1 )
      {
        if( true == $this->gefunden() )
        {
          $this->debug( "cF" );
          $this->debug();
          return true;
        }
      }
    }
    /***
    ***/
    return true;
  }
  function parentTokenMarkiert( $tID )
  {
    /*** 
     *** [0] Token [1] Gewicht [2] Thema [3] Topic [4] Topic.ID [5] gefunden-Stelle [6] Token.ID [7] TopicToken.ID
     ***/
    while( $tID = DB::gibFeld( "SELECT tst. TokenID FROM TokenSubToken tst JOIN SubToken st ON (tst. SubTokenID=st.ID) JOIN Token t ON (tst. TokenID=t.ID) WHERE " . $tID . "=st. TokenID" ) )
    { // hat irgendein Parent-Token bereits markiert?
      for( $i=0; $i < count($this->a); $i += $this->dim )
        if( $this->a[$i+1] ) // markierten Token gefunden
          return true;
    }
    return false;
  }
  function debug( $w = "range" )
  {
    switch( $w )
    {
      case "range":
        for( $i=0; $i < count($this->a); $i += $this->dim )
          echo $this->a[$i] . " - " . $this->a[$i+1] . " - " . $this->a[$i+2] . " - " . $this->a[$i+3] . " - " . $this->a[$i+4] . " - " . $this->a[$i+5] . "<br>";
      break;
      case "cF":
        echo "Zeile " . $this->cZeile . ": " . $this->cFelder . "Felder<br>";
      break;
    }
  }
  function reset()
  {
    for( $i=0; $i < count($this->a); $i += $this->dim )
      $this->a[$i+1] = $this->a[$i+5] = 0; // loescht die Anzahl der erkannten Token
  }
  function close()
  {
    parent::reset();
  }
  function open()
  {
    parent::open();
  }
}
