<?php
class KW extends DateTime
{
  private $ID;
  private $KW;
  private $wochenTag;
  private $zeit;
  private $tag;
  private $datum;

  function __construct($time)
  {
    date_default_timezone_set('Europe/Berlin');
    $this->tag = array (
      "So",
      "Mo",
      "Di",
      "Mi",
      "Do",
      "Fr",
      "Sa"
    );
    $this->KW = date( "W" );
    $this->wochenTag = date( "w" );
    $this->datum = date( "j.n." );
    $this->zeit = $time;
    //parent::__construct($time);
    parent::__construct();
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return $this->datum;
      case 'Kalenderwoche':
        return $this->KW;
      case 'Wochentag':
        return $this->tag[$this->wochenTag];
      case 'eilt':
        //return parent::__get('eilt');
      default:
        throw new Exception("KW hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
