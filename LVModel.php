<?php
require_once("LVParser.php");
class LVModel extends LVParser
{
  protected $fSimpleMode; // einfacher oder komplexer Versuch der Erkennung
  protected $LVID;        // prim. key der LV - Instanz

  function __construct($d, $thema=1, $czeile=0, $fRec=0, $mode="r")
  {
    parent::__construct($d, $thema, $czeile, $fRec, $mode);
    $this->fSimpleMode = true;
    $this->LVID = 1; // hart verdrahtet, solange noch kein GUI
  }
  function __get($var)
  {
    switch($var)
    {
      case 'vollTreffer': // vor dem naechsten erkannten Token kamen erst Zeilen mit nicht erkannten Token
        return parent::__get('vollTreffer');
      case 'lesbar':
        return parent::__get('lesbar');
      case 'gibLaengeReihe':
        return parent::__get('gibLaengeReihe');
      case 'gibPfad':
        return parent::__get('gibPfad');
      case 'gibReihe':
        return parent::__get('gibReihe');
      case 'gibZeile':
        return parent::__get('gibZeile');
      case 'gibZeilenZaehler':
        return parent::__get('gibZeilenZaehler');
      case 'Thema':
        return parent::__get('Thema');
      default:
        throw new Exception("LVModel hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function thematisieren( &$thema )
  {
    echo "\n" . $this->gibPfad . " mit Thema " . $this->Thema . "<br>";
    if( false == parent::thematisieren( $thema ) )
    {
      echo "\n<br>:-(( ";
      return;
    }
    echo "\n<br>:-)! ";
    $this->dumpFundstelle();
    if( true == $this->fSimpleMode )
      $this->storeSimple( $thema );
  }

  function storeSimple( $thema )
  {
    if( !$this->fRecord )
      return;
    if( !isset($this->buffer[$this->cursor]) )
    {
      echo "\n<br>Nil-Cursor!";
      return;
    }
    // gibt's schon was?
    if( !DB::gibFeld( "SELECT COUNT(*) FROM Zeile WHERE " . $this->LVID . "=LVID" ) )
    { // no nix passiert: Spalte fuer Positionen anlegen
      Db::insert( "INSERT INTO Spalte VALUES ( null, " . $this->LVID . ", 0, " . "'Pos' )", $sID );
      for ($i=0; $i <= $this->cursor; $i++)
      {
        Db::insert( "INSERT INTO Zeile VALUES ( null, " . $this->LVID . ", " . $i . " )", $zID );
        $subPos = $i + 1;
        Db::insert( "INSERT INTO Zelle VALUES ( null, " . $sID . ", " . $zID . ", '1.$subPos' )");
      }
    }
    if( 2 == $this->Thema )
    {
    }
    echo "\n Thema: " . $this->Thema . "<br>";
    return true;
  }
  function dumpFundstelle()
  {
    if( !$this->fRecord )
      return;
    if( !isset($this->buffer[$this->cursor]) )
    {
      echo "\n<br>Nil-Cursor!";
      return;
    }
    $cF = count($this->buffer[$this->cursor]); // Anzahl Felder auslesen
    echo "\n<br>Cursor = " . $this->cursor;
    for ($c=0; $c < $cF; $c++)
    {
      unset($_s);
      $_s = explode( " ", utf8_encode($this->buffer[$this->cursor][$c]) );
      if( $c == $this->icsVal )
        echo ", " . $this->icsVal . ". csv-Feld";
      for( $s=0; $s < count($_s); $s++ )
      {
        if( $c == $this->icsVal && $s == $this->iBlVal )
          echo ", " . $this->iBlVal . ". blank-sep. Wort: ";
        echo $_s[$s] . " ";
      }
    }
  }

  function speichernThema()
  {
    if( !$this->fRecord )
      return false;
    if( !isset($this->buffer[$this->cursor]) )
    {
      echo "\n<br>Nil-Cursor!";
      return false;
    }
    $cF = count($this->buffer[$this->cursor]); // Anzahl Felder auslesen
    echo "\n<br>Cursor = " . $this->cursor;
    for ($c=0; $c < $cF; $c++)
    {
      unset($_s);
      $_s = explode( " ", utf8_encode($this->buffer[$this->cursor][$c]) );
      if( $c == $this->icsVal )
        echo ", " . $this->icsVal . ". csv-Feld";
      for( $s=0; $s < count($_s); $s++ )
      {
        if( $c == $this->icsVal && $s == $this->iBlVal )
          echo ", " . $this->iBlVal . ". blank-sep. Wort: ";
        echo $_s[$s] . " ";
      }
    }
  }
}
