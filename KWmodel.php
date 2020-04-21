<?php
require_once("Db.php");
require_once("KW.php");
class KWmodel extends KW
{
  static protected $db; // db->db : DB-Handle
  protected $tag;
  private   $go;   // fruehester Betreuungsbeginn
  private   $stop; // spaetestes Betreuungsende
  private   $filter;

  function __construct($strDate, $filter="")
  {
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    $this->filter = $filter;
    $this->db = Db::getInstance();
    // Start-Quart am Morgen:
    //$this->go = DB::gibFeld( "SELECT IF(4 < MIN(v.ID), MIN(v.ID)-4, 1) FROM VS v JOIN KlientVS cv ON (v.ID=cv.VSID) JOIN MAKlientVS mcv ON (cv.ID=mcv.KlientVSID)", 0 );
    $this->go = DB::gibFeld( "SELECT IF(4 < MIN(v.ID), MIN(v.ID)-4, 1) FROM VS v JOIN Termin te ON (v.ID=te.VSID)", 0 );
    // Ende-Quart am Abend:
    //$this->stop = DB::gibFeld( "SELECT IF(v.ID + cv.Menge > 96, 96, v.ID + cv.Menge) FROM VS v JOIN KlientVS cv ON (v.ID=cv.VSID) JOIN MAKlientVS mcv ON (cv.ID=mcv.KlientVSID) ORDER BY v.ID DESC LIMIT 1", 0 );
    $this->stop = DB::gibFeld( "SELECT IF(v.ID + te.Dauer > 96, 96, v.ID + te.Dauer) FROM VS v JOIN Termin te ON (v.ID=te.VSID) ORDER BY v.ID DESC LIMIT 1", 0 );
    if( !$this->stop )
    {
      $this->go   = 31;
      $this->stop = 33;
    }
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, "go: " . $this->go . " -- stop: " . $this->stop );
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
      case 'WochentagNumerisch':
        return parent::__get('WochentagNumerisch');
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
    $a[0]=0;// hier Feld 0 rein = Dauer
    $a[1]=1;// hier Feld 1 rein = Initialen
    $a[2]=2;// hier Feld 2 rein = Name, Vorname
    $a[3]=3;// hier Feld 3 rein = Trainer.ID
    $a[4]=4;// hier Feld 4 rein = Termin.ID
    $a[5]=5;// hier Feld 5 rein = Ort.Kuerzel
    $a[6]=6;// hier Feld 6 rein = Ort.ID
    $a[7]=7;// hier Feld 7 rein = te.TerminartID
    $a[8]=8;// hier Feld 8 rein = te.KWID
    $dim=count($a);
    if( 1/*'ort' == $what*/ )
    {
      /*###*/
      //$sql = "SELECT te.Dauer, " . $concat . " AS sc, CONCAT(LEFT(tr.Name,1),LEFT(tr.Vorname,1)), tr.ID, te.ID, CONCAT(o.Kursort,'-',o.Ortschaft), o.ID FROM Termin te JOIN Trainer tr ON te.TrainerID=tr.ID JOIN Ort o ON te.OrtID=o.ID JOIN Jahr j ON (te. JahrID =j.ID) JOIN KW k ON (te. KWID =k.ID) JOIN Tag t ON (te. TagID =t.ID) JOIN VS v ON (te. VSID =v.ID) WHERE $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID $this->filter ORDER BY sc";
      /*** 29.3.20: Nur noch Trainer-Initialen und Ort-Kuerzel ***/
      $sql = "SELECT te.Dauer, " . $concat . " AS sc, CONCAT(LEFT(tr.Vorname,1),LEFT(tr.Name,1)), tr.ID, te.ID, te.Kuerzel, o.ID, te.TerminartID, te.KWID FROM Termin te JOIN Trainer tr ON te.TrainerID=tr.ID JOIN Ort o ON te.OrtID=o.ID JOIN Jahr j ON (te. JahrID =j.ID) JOIN KW k ON (te. KWID =k.ID) JOIN Tag t ON (te. TagID =t.ID) JOIN VS v ON (te. VSID =v.ID) WHERE $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID $this->filter ORDER BY sc";
    }
    else
    {
      $sql = "SELECT te.Dauer, CONCAT(LEFT(tr.Name,1),LEFT(tr.Vorname,1)), CONCAT(tr.Name,' ',tr.Vorname), tr.ID, te.ID, CONCAT(LEFT(tr.Name,1),LEFT(tr.Vorname,1)), o.ID FROM Termin te JOIN Trainer tr ON te.TrainerID=tr.ID JOIN Ort o ON te.OrtID=o.ID JOIN Jahr j ON (te. JahrID =j.ID) JOIN KW k ON (te. KWID =k.ID) JOIN Tag t ON (te. TagID =t.ID) JOIN VS v ON (te. VSID =v.ID) WHERE $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID $this->filter ORDER BY sc";
      /*###*/
    }
    //echo $sql . "<br>";
    DB::gibFelderArray( $sql, $a );
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, $sql );
  }
  /***
   *** fMA : filter MA
   ***/
}
