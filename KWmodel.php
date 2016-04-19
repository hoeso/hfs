<?php
require_once("Db.php");
require_once("KW.php");
class KWmodel extends KW
{
  static protected $db; // db->db : DB-Handle
  protected $tag;
  private   $go;   // fruehester Betreuungsbeginn
  private   $stop; // spaetestes Betreuungsende

  function __construct($strDate)
  {
    $this->db = Db::getInstance();
    // Start-Quart am Morgen:
    $this->go = DB::gibFeld( "SELECT IF(4 < MIN(v.ID), MIN(v.ID)-4, 1) FROM VS v JOIN ClientVS cv ON (v.ID=cv.VSID) JOIN MAClientVS mcv ON (cv.ID=mcv.ClientVSID)", 0 );
    // Ende-Quart am Abend:
    $this->stop = DB::gibFeld( "SELECT IF(v.ID + cv.Menge > 96, 96, v.ID + cv.Menge) FROM VS v JOIN ClientVS cv ON (v.ID=cv.VSID) JOIN MAClientVS mcv ON (cv.ID=mcv.ClientVSID) ORDER BY v.ID DESC LIMIT 1", 0 );
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'DatumEU':
        return parent::__get('DatumEU');
      case 'Go':
        return $this->go;
      case 'Jahr':
        return parent::__get('Jahr');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      case 'Stop':
        return $this->stop;
      default:
        throw new Exception("KWmodel hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
