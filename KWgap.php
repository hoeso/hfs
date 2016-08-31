<?php
require_once("Db.php");
require_once("KW.php");
class KWgap extends KW
{
  static protected $db; // db->db : DB-Handle
  protected $tag;
  private $kw;

  function __construct($mID, $kw)
  {
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    $this->kw = $kw;
    $this->db = Db::getInstance();
    // Anfang Abwesenheit:
    //$this->go = DB::gibFeld( "SELECT IF(4 < MIN(v.ID), MIN(v.ID)-4, 1) FROM VS v JOIN ClientVS cv ON (v.ID=cv.VSID) JOIN MAClientVS mcv ON (cv.ID=mcv.ClientVSID)", 0 );
    //var_dump($this->tag); echo "\n<br>";
    if( isset($_REQUEST["d"]) )
      ;//dEcho( $b_, "go: " . $this->go . " -- stop: " . $this->stop );
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'DatumEU':
        return parent::__get('DatumEU');
      case 'Jahr':
        return parent::__get('Jahr');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      case 'Montag':
        return parent::__get('Montag');
      default:
        throw new Exception("KWgap hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
