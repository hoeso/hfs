<?php
require_once("Datei.php");
class CSV extends Datei
{
  function __construct($d, $mode="r")
  {
    parent::__construct($d, $mode);
  }
  function __get($var)
  {
    switch($var)
    {
      case 'lesbar':
        return parent::__get('lesbar');
      case 'gibZeile':
        return fgetcsv( parent::__get('handle') );
      default:
        throw new Exception("CSV hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
