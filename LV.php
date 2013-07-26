<?php
require_once("ParserCSV.php");
class LV extends ParserCSV
{
  private $a; // Vektor mit TopicToken-Treffern
  private $dim; // TopicToken-Dimension
  private $step; // Das aktuelle Parse-Thema
  private $cZeile; // Zeilen Counter
  private $cFelder; // Anzahl Felder in der Zeile
  private $nFeld; // n.tes Feld in der Zeile
  private $z; // Felder der naechsten Zeile
  function __construct($d, $mode="r")
  {
    parent::__construct($d, $mode);
    $this->step = 1;
    unset($this->z);
    $this->cZeile = 0;
    $this->cFelder = 0;
    $this->nFeld = 0;
    $this->a[0]=0;// hier Feld 0 rein = Token
    $this->a[1]=1;// hier Feld 1 rein = Gewicht
    $this->a[2]=2;// hier Feld 2 rein = Rang
    $this->a[3]=3;// hier Feld 3 rein = Topic
    $this->dim = count($this->a);
    DB::gibFelderArray( "SELECT t.Token, 0, tp.Rang, tp.Topic FROM TopicToken tt JOIN Topic tp ON (tt.TopicID=tp.ID) JOIN Token t ON (tt.TokenID=t.ID)", $this->a );
  }
  function __get($var)
  {
    switch($var)
    {
      case 'lesbar':
        return parent::__get('lesbar');
      case 'gibZeile':
        return parent::__get('gibZeile');
      default:
        throw new Exception("LV hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function finden()
  {
    /*** Token als einzelnes Wort: Gewichtung = 2.
     *** Token kommt in Wort vor: Gewichtung = 1.
     *** Fuer die einzelnen Topics eine Enitaet hinterlegen mit
     *** einer Mindestgewichtung, z.B. Ueberschrift : 2
     ***/
    $z = array();
    while( false <> $this->z = $this->gibZeile )
    {
      if( false == $this->z && !$this->cZeile )
        return false; // keine einzige Zeile bekommen, da stimmt was nicht
      $z[] = $this->z;
      $f = false;
      $this->reset(); // loescht alle Token-Treffer
      ++$this->cZeile;
      $this->cFelder = count($this->z); // Anzahl Felder auslesen
      $this->debug( "cF" );
      for ($c=0; $c < $this->cFelder; $c++)
        for( $i=0; $i < count($this->a); $i += $this->dim )
          if( strstr( utf8_encode($this->z[$c]), $this->a[$i] ) )
          {
            ++$this->a[$i+1]; // gefundenen Token markieren
            $f = true;
          }
      if( true == $f )
        $this->debug();
    }
    $c = count( $z );
    echo "<p>zeilen : $c<br>";
    for( $i=0; $i<$c; $i++ )
    {
      $f = count($z[$i]);
      echo "<p>felder z[$i]: $f<br>";
      for ($k=0; $k < $f; $k++)
        echo utf8_encode($z[$i][$k]) . "<br />\n";
    }
    echo "<p>";
    return true;
  }
  function debug( $w = "range" )
  {
    switch( $w )
    {
      case "range":
        for( $i=0; $i < count($this->a); $i += $this->dim )
          echo $this->a[$i] . " - " . $this->a[$i+1] . " - " . $this->a[$i+2] . " - " . $this->a[$i+3] . "<br>";
      break;
      case "cF":
        echo "Zeile " . $this->cZeile . ": " . $this->cFelder . "Felder<br>";
      break;
    }
  }
  function reset()
  {
    for( $i=0; $i < count($this->a); $i += $this->dim )
      $this->a[$i+1] = 0; // loescht die Anzahl der erkannten Token
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
