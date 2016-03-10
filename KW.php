<?php
class KW extends DateTime
{
  private $ID;
  private $KW;
  private $wochenTag;
  private $zeit;
  private $tag;
  private $datum;
  private $heute;

  function __construct($time)
  {
    date_default_timezone_set('Europe/Berlin');
    $this->tag = array (
      "So" => "",
      "Mo" => "",
      "Di" => "",
      "Mi" => "",
      "Do" => "",
      "Fr" => "",
      "Sa" => ""
    );
    var_dump($this->tag); echo "\n<br>";
    $this->KW = date( "W" );
    $this->wochenTag = date( "w" );
    $this->datum = date( "j.n." );
    $this->heute = date( "Y-m-d" );
    $this->zeit = $time;
    $c = 0;
    foreach ($this->tag as $key => &$value)
    {
      if( $c == $this->wochenTag )
      {
        $value = $this->datum;
	$this->tag["$key"] = $this->datum;
	break;
      }
      ++$c;
    }
    var_dump($this->tag); echo "\n<br>";
    echo $this->tag['Do'] . "<br>";
    //$datum = new DateTime($this->heute);
    $datum = new DateTime(date( "Y-m-d" ));
    $gestern = new DateTime(date( "Y-m-d" ));
    date_sub($gestern,date_interval_create_from_date_string("1 days"));
    //$datum = parent::sub($this->heute,"1 day");

    echo "heute: " . $datum->format("j.n.") . "; gestern: " . $gestern->format("j.n.");
    //echo "heute: " . $this->heute
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
