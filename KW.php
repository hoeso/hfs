<?php
class KW
{
  private $KW;
  private $wochenTag;
  private $tag;

  function __construct()
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
    //var_dump($this->tag); echo "\n<br>";
    $this->KW = date( "W" );
    $this->wochenTag = date( "w" );
    $c = 0;
    foreach ($this->tag as $key => &$value)
    {
      $datum = new DateTime(date( "Y-m-d" ));
      if( $c == $this->wochenTag )
      {
        $value = $datum->format("j.n.");
      }
      else if( $c < $this->wochenTag )
      {
        
        date_sub($datum,date_interval_create_from_date_string( $this->wochenTag - $c . " days" ));
        $value = $datum->format("j.n."); 
      }
      else if( $c > $this->wochenTag )
      {
        
        date_add($datum,date_interval_create_from_date_string( $c - $this->wochenTag . " days" ));
        $value = $datum->format("j.n."); 
      }
      ++$c;
    }
    foreach ($this->tag as $key => &$value)
      echo $key . " " . $value . "    ";
  }
  function __get($var)
  {
    switch($var)
    {
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
