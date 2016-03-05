<?php
class KW extends DateTime
{
  private $ID;
  private $KW;
  private $zeit;

  function __construct($time)
  {
    date_default_timezone_set('Europe/Berlin');
    $this->KW = date( "W" );
    $this->zeit = $time;
    //parent::__construct($time);
    parent::__construct();
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Kalenderwoche':
        return $this->KW;
      case 'eilt':
        //return parent::__get('eilt');
      case 'Nummer':
        return $this->Nummer;
      default:
        throw new Exception("KW hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
