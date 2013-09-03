<?php
require_once("LVModel.php");
class LVView extends LVModel
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
        throw new Exception("LVView hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function thematisieren( &$thema )
  {
    if( false == parent::thematisieren( $thema ) )
    {
      return;
    }
  }
  function display( $lvid )
  {
  }
}
