<?php
class Db
{
  public $link;
  public $db;

  static private $instance = null;

  static public function getInstance()
  {
    if (null === self::$instance)
    {
      self::$instance = new self;
    }
    return self::$instance;
  }

  private function __construct(){}
  private function __clone(){}

  static public function insert( $str, &$key=0 )
  {
    $a = explode( " ", $str );
    $entity = "";
    for( $s=0; $s < count($a); $s++ )
      if( "INTO" == strtoupper($a[$s]) )
      {
        $entity = $a[$s+1];
        break;
      }
    if( !$entity )
    {
      throw new Exception("FEHLER: $str enthaelt keine Tabellenangabe.", 2 );
    }
    $result = mysql_db_query( self::$instance->db, $str );
    if(!$result)
      throw new Exception("FEHLER: $str<br>.", 1 );

    $result = mysql_db_query( self::$instance->db, "SELECT LAST_INSERT_ID() FROM " . $entity, self::$instance->link );
    if(!$result)
      throw new Exception("FEHLER: $entity<br>.", 2 );
    $a_ = mysql_fetch_row( $result );
    mysql_free_result( $result );

    $key = $a_[0];
  }

  static public function insertOnly( $str )
  {
    $result = mysql_db_query( self::$instance->db, $str );
    if(!$result)
      throw new Exception("FEHLER: $str<br>.", 1 );
  }

  // gibFeld
  // Input:
  //	$sql: Select
  //	$iFeld: das iFeld.te Feld soll zurueckgegeben werden
  //
  static public function gibFeld( $sql, $iFeld=0 )
  {
    $result = mysql_db_query( self::$instance->db, $sql );
    if(!$result)
      throw new Exception("FEHLER: $sql<br>.", 1 );
    $arr = mysql_fetch_row( $result );
    mysql_free_result( $result );
    return $arr[ $iFeld ];	
  }

  static public function delete( $str )
  {
   $result = mysql_db_query( self::$instance->db, $str );
    if(!$result)
      throw new Exception("FEHLER beim Delete: $str<br>.", 1 );
  }

  // gibFelderArray
  // Input:
  //	$sql: Select
  //	$arrFeld: der Feld-Vektor soll gefuellt zurueckgegeben werden
  //              Die Elemente des Feld-Vektors sind, beginnend bei 0,
  //              mit dem Index der aufzunehmenden Spalte aus der
  //              Treffermenge belegt
  //
  static public function gibFelderArray( $sql, &$arrFeld )
  {
    $arrTmp=$arrFeld;
    $anz=count($arrTmp);
    $result = mysql_db_query( self::$instance->db, $sql );
    if(!$result)
      reagierenAufSQLFehler( $link, $sql, $PKViolation );
    $nTreffer = mysql_num_rows( $result );
    $j=0;
  
    for( $i=0; $i<$nTreffer;$i++ )      // ueber alle Datensaetze
    {
      $arr = mysql_fetch_row( $result );
      for($k=0;$k<$anz;$k++)
      {
        $arrFeld[ $j++ ] = $arr[ $arrTmp[ $k ] ];
      }
    }
    mysql_free_result( $result );
  }

  // gibFeldArray
  // Input:
  //	$sql: Select
  //	$arrFeld: der Feld-Vektor soll gefuellt zurueckgegeben werden
  //              mit den Werten eines einzigen Feldes
  //
  static public function gibFeldArray( $sql, $iFeld, &$arrFeld )
  {
    $result = mysql_db_query( self::$instance->db, $sql );
    if(!$result)
      reagierenAufSQLFehler( $link, $sql, $PKViolation );

    $nTreffer = mysql_num_rows( $result );
    for( $i=0; $i<$nTreffer;$i++ )      // ueber alle Datensaetze
    {
      $arr = mysql_fetch_row( $result );
      $arrFeld[$i] = $arr[$iFeld];
    }
    mysql_free_result( $result );
  }
}
