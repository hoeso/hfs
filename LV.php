<?php
require_once("ParserLV.php");
class LV extends ParserLV
{
  function __construct($d, $thema=1, $czeile=0, $fRec=0, $mode="r")
  {
    parent::__construct($d, $thema, $czeile, $fRec, $mode);
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
        throw new Exception("LV hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function thematisieren()
  {
    echo "\n" . $this->gibPfad . " mit Thema " . $this->Thema . "<br>";
    if( false == parent::thematisieren() )
    {
      echo "\n<br>:-(( ";
      return;
    }
    echo "\n<br>:-)! ";
    $this->dumpFundstelle();
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
