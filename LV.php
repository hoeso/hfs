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
  private $bearbeitenThema; // Vektor mit den "Themen": Gemeint sind die Spalten des LV
  private $fRecord; // Zeilen "mitschneiden" (=speichern)
  private $iBuf;   // interner Pufferzeiger
  private $buffer; // interner Puffer fuer die interpretierten Zeilen
  function __construct($d, $thema=1, $czeile=0, $fRec=0, $mode="r")
  {
    parent::__construct($d, $mode);
    $this->thema = $thema;
    unset($this->z);
    $this->cZeile = $czeile;
    $this->cFelder = 0;
    $this->nFeld = 0;
    $this->fRecord = $fRec;
    if( $fRec )
      $iBuf=0; // $this->buffer auf Anfang setzen
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
  function tokenHatDasFormat( $t, $fmt )
  {
    switch( $fmt )
    {
      case "d.": // nachm Punkt darf nix mehr kommen
        for( $i=0; $i<strlen($t); $i++ )
          if( '.' == $t[$i] || !is_numeric($t[$i]) )
            break;
        if( !isset($t[$i]) || ('.' <> $t[$i]) ) // Punkt kam nicht vor
          return false;     // o. vor . nicht-num. Char
        if( isset($t[$i+1]) && ' ' <> $t[$i+1] ) // nach Punkt kommt noch was anderes als ein Blank
          return false;
      return true;
      case "d": // keine Trennzeichen wie . oder ,
        if( !strlen($t) )
          return false;
        for( $i=0; $i<strlen($t); $i++ )
        {
          echo "[" . $t[$i] . "](" . ord($t[$i]) . ")";
          if( '0' > $t[$i] || '9' < $t[$i] )
            return false;
        } 
      return true;
      default:
        echo "unbekanntes Pr&uuml;fformat $fmt ?<br>";
      return false;
      /*
        for( $i=0; $i<strlen($t); $i++ )
          echo "[" . $t[$i] . "] ";
        echo " | ";
       */
    }
    return false;
  }
  function findenThemaToken( $aF, $iSpalte )
  {
    /*** jeden Token pruefen, ob er das Format  ***
     *** bedient                                ***/
    while( false <> $this->z = $this->gibZeile )
    {
      if( false == $this->z && !$this->cZeile )
        return false; // sind wir schon fertig?
      ++$this->cZeile;
      if( $this->fRecord ) // aufzeichnen!
      {
        $this->buffer[ $this->iBuf ] = $this->z;
        ++$this->iBuf;
      }
      $this->cFelder = count($this->z); // Anzahl Felder auslesen
      for( $i=0; $i < count($aF); $i++ )
      {
        for ($c=0; $c < $this->cFelder; $c++)
        {
          unset($_s);
          $_s = explode( " ", utf8_encode($this->z[$c]) );
          echo "Format | ";
          echo $aF[$i] . " |?";
          for( $s=0; $s < count($_s); $s++ )
          {
            echo "<br>[" . $_s[$s] . "] (" . ord($_s[$s]) . ")";
            if( true == $this->tokenHatDasFormat( $_s[$s], $aF[$i] ) )
            {
              echo " -- " . $_s[$s] . " wurde erkannt auf Format " . $aF[$i] . "<br>";
              // Hilfe: Was jetzt? Weiterschalten auf naechstes Thema?
              // vorher speichern?
              /*** naechste Zeile pruefen: Wenn dort erkanntes Format laenger ist, dann
               *** scheint das hier ein Paragraph zu sein
               ***/
              for( $j=0; $j<$this->iBuf; $j++ )
                echo $this->buffer[$j] . " -;- ";
              return true;
            }
          }
        }
        echo "<br>";
      }
    }
    return false;
  }
  function thematisieren()
  {
    /*** FF 2. Bei leerer Treffermenge mit aktuellem Thema in der Token-Liste verzweigen zum TopicTokenThema-Eintrag ***/
    /*** $this->reihe[0] pruefen auf TopicTokenID und damit verzweigen zum TopicTokenThema-Eintrag ***/
    if( !isset($this->bearbeitenThema) )
      return false;
    for( $i=0; $i<count($this->bearbeitenThema); $i++ )
    {
      if( !isset($this->bearbeitenThema[$i]) )
        return false;

      if( !$thID = DB::gibFeld( "SELECT ThemaID FROM TopicTokenThema WHERE " . $this->bearbeitenThema[$i] . "=TopicTokenID" ) )
      {
        echo "SubToken?<br>";
    
        $a[0]=0;// hier Feld 0 rein = TopicID
        $a[1]=1;// hier Feld 1 rein = TokenID
        DB::gibFelderArray( "SELECT TopicID, TokenID FROM TopicToken WHERE " . $this->bearbeitenThema[$i] . "=ID", $a );
        if( !$thID = DB::gibFeld( "SELECT ThemaID FROM TopicTokenThema ttt JOIN TopicToken tt ON (ttt. TopicTokenID=tt.ID) JOIN TokenSubToken tst ON(tt. TokenID=tst.TokenID) JOIN SubToken st ON (tst. SubTokenID=st.ID) WHERE " . $a[1] . "=st. TokenID AND " . $a[0] . "=tt. TopicID" ) )
        {
          echo "kein Thema gefunden<br>";
          return false;
        }
        echo "SubToken.<br>";
      }
      else
        echo "Token<br>";
      $aF = array();
      DB::gibFeldArray( "SELECT f. Format FROM ThemaFormat thf JOIN Format f ON (thf. FormatID=f.ID) WHERE " . $thID . "=thf.ThemaID ORDER BY Format DESC", 0, $aF );
      if( !count( $aF ) )
      {
        echo "keine Formate zum Thema gefunden<br>";
        return false;
      }
      /*** Thema gefunden, jetzt die Formate dazu ***
       ***                                        ***/
      return $this->findenThemaToken( $aF, $i );
      while( false <> $this->z = $this->gibZeile )
      {
        if( false == $this->z && !$this->cZeile )
          return false; // sind wir schon fertig?
        if( $this->fRecord ) // aufzeichnen!
        {
          $this->buffer[ $this->iBuf ] = $this->z;
          ++$this->iBuf;
        }
        ++$this->cZeile;
        $this->cFelder = count($this->z); // Anzahl Felder auslesen
        for ($c=0; $c < $this->cFelder; $c++)
        {
          unset($_s);
          $_s = explode( " ", utf8_encode($this->z[$c]) );
          for( $s=0; $s < count($_s); $s++ )
            echo $_s[$s] . ", ";
          echo "<br>";
        }
      }
    }
    return false;
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
    if( false == habWas( $this->a, 0, 7 ) )
    { // nix gfundn. Dann geht's vielleicht ums Thema?
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
          ++$this->cZeile; // auf Zeile hinter der Ueberschrift positionieren zum Weitermachen
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
  function anlegenThemenPool( $c )
  {
    unset( $this->bearbeitenThema );
    $this->bearbeitenThema = array();
    for( $i=0; $i<$c; $i++ )
      $this->bearbeitenThema[$i]=0;
  }
  function hinzufuegenThema( $i, $t )
  {
    $this->bearbeitenThema[$i]=$t;
  }
}
