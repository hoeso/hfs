<?php
require_once("Db.php");
class MAAbwesenheit
{
  private   $jahr;
  private   $ymd;
  private   $maID;
  private   $abwesenheitsGrund;
  private   $von;
  private   $bis;
  function __construct($jahr, $tag, $MAID)
  {
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    $this->jahr = $jahr;
    $this->ymd = $tag;
    $this->maID = $MAID;
    $this->von = $this->bis = '00.00';
    
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, "$jahr - $tag - $MAID" );
    $d_[0]=0;// hier Feld 0 rein = Beginn (der Abwesenheit)
    $d_[1]=1;// hier Feld 1 rein = Ende      ./.
    $d_[2]=2;// hier Feld 2 rein = Grund     ./.
    $d_dim=count($d_);
    $sql_ = "SELECT Beginn, Ende, Grund FROM MAAbwesenheit WHERE " . $this->maID . "=MAID AND ((YEAR(Beginn) = '" . $this->jahr . "' AND YEAR(Ende) >= '" . $this->jahr . "') OR (YEAR(Beginn) <= '" . $this->jahr . "' AND YEAR(Ende) = '" . $this->jahr . "'))";
    $this->db = Db::getInstance();
    DB::gibFelderArray( $sql_, $d_ );
    //gibFelderArray( $MySQLDb, $sql_, $d_ );
    if( true == habWas( $d_, 0, 2 ) )
    {
      if( isset($_REQUEST["d"]) )
        dEcho( $b_, $sql_ );
      /*** faellt das zu planende Datum in eine Abwesenheit?
       ***/
      for( $j=0; $j<count($d_); $j += $d_dim )
      {
        if( isset($_REQUEST["d"]) )
          dEcho( $b_, $d_[$j] . " + " . $d_[$j+1] . ": " . $d_[$j+2] );
        if( $d_[$j] <= $this->ymd && $this->ymd <= $d_[$j+1] )
        {
          $this->abwesenheitsGrund = $d_[$j+2];
          $this->von = $d_[$j];   // von, Format 'd.m.'
          $this->bis = $d_[$j+1]; // bis,     ./.
        }
      }	
    }
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Status':
        return $this->abwesenheitsGrund;
      case 'abwesend':
        if( '00.00' == $this->von )
	  return false;
	return true;
      case 'vonBis':
        $v = explode( "-", $this->von );   // von, Format 'd.m.'
        $b = explode( "-", $this->bis );   // bis, Format 'd.m.'
	return "$v[2].$v[1]. - $b[2].$b[1].";
      default:
        throw new Exception("MAAbwesenheit hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
