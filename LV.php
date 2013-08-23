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
    if( false == parent::thematisieren() )
    {
      echo "\n<br>:-(( ";
      return;
    }
    echo "\n<br>:-)! ";
    $this->dumpFundstelle();
  }
}
