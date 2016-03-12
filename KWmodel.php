<?php
require_once("KW.php");
class KWmodel extends KW
{
  static protected $db; // db->db : DB-Handle
  protected $tag;

  function __construct($strDate)
  {
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
    $this->db = Db::getInstance();
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
        throw new Exception("KWmodel hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}

