<?php
require_once("CSV.php");
class ParserCSV extends CSV
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
        return parent::__get('gibZeile');
      default:
        throw new Exception("ParserCSV hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function reset()
  {
    parent::reset();
  }
  function open()
  {
    parent::open();
  }
}
