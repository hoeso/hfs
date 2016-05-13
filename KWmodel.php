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
      case 'Montag':
        return parent::__get('Montag');
      default:
        throw new Exception("KWmodel hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function gibTermine( &$a, &$dim, $what, $concat, $dayofweek, $row )
  {
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    $a[0]=0;// hier Feld 0 rein = Menge
    $a[1]=1;// hier Feld 1 rein = Initialen
    $a[2]=2;// hier Feld 2 rein = Name, Vorname
    $a[3]=3;// hier Feld 3 rein = [Client|MA].ID
    $a[4]=4;// hier Feld 4 rein = [MAClientVS].ID
    $a[5]=5;// hier Feld 5 rein = Initialen der jeweils anderen Person
    $a[6]=6;// hier Feld 6 rein = [ClientVS].ID
    $dim=count($a);
    if( 'client' == $what )
    {
      $sql = "SELECT cv.Menge, " . $concat . " AS sc, CONCAT(c.Name,',',c.Vorname), c.ID, mcv.ID, CONCAT(LEFT(m.Name,1),LEFT(m.Vorname,1)), cv.ID FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN MAClient mc ON (mcv. MAClientID =mc.ID) JOIN MA m ON (mc.MAID=m.ID) JOIN Client c ON (cv. ClientID =c.ID) JOIN Jahr j ON (cv. JahrID =j.ID) JOIN KW k ON (cv. KWID =k.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID ORDER BY sc";
    }
    else
    {
      $sql = "SELECT cv.Menge, CONCAT(LEFT(m.Name,1),LEFT(m.Vorname,1)), CONCAT(m.Name,',',m.Vorname), m.ID, mcv.ID, CONCAT(LEFT(c.Name,1),LEFT(c.Vorname,1)), cv.ID FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN MAClient mc ON (mcv. MAClientID =mc.ID) JOIN MA m ON (mc.MAID=m.ID) JOIN Client c ON (cv. ClientID =c.ID) JOIN Jahr j ON (cv. JahrID =j.ID) JOIN KW k ON (cv. KWID =k.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE mc.ClientID=cv.ClientID AND $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID ORDER BY sc";
    }
    DB::gibFelderArray( $sql, $a );
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, $sql );
  }
  function gibKlient( &$a, &$dim, $j, $kw, $t )
  {
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    $a[0]=0;// hier Feld 0 rein = c.Name, c.Vorname
    $dim=count($a);
    $sql = "SELECT DISTINCT CONCAT(c.Name,',',c.Vorname) AS Klient FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN MAClient mc ON (mcv. MAClientID =mc.ID) JOIN MA m ON (mc.MAID=m.ID) JOIN Client c ON (cv. ClientID =c.ID) JOIN Jahr j ON (cv. JahrID =j.ID) JOIN KW k ON (cv. KWID =k.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE $j=j.ID AND $kw=k.ID AND $t=t.ID ORDER BY v.ID";
    DB::gibFelderArray( $sql, $a );
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, $sql );
  }
}
