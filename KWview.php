<?php
require_once("KWmodel.php");
class KWview extends KWmodel
{
  protected $tag;

  function __construct($strDate)
  {
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      default:
        throw new Exception("KWview hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function show()
  {
    $i=0;
    foreach ($this->tag as $key => $value)
    {
      if( $i )
        echo $key . " " . $value . "    ";
      ++$i;
    }
  }
}
