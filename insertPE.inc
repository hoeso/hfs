<?php
$debug=0;
if( isset($backupSELECTSL1) and $backupSELECTSL1 )
  $ActionSuffix = "&TabelleSL1=$TabelleSL1&backupSELECTSL1=$backupSELECTSL1";
$HTTP_POST_VARS = $_POST;
if( isset( $HTTP_POST_VARS ) )
  reset( $HTTP_POST_VARS );
else
  return;
// Das 1. Feld ist immer der AUTOINKREMENT-Primaerschluessel
$sql = "INSERT INTO {$_E['entitaet']} VALUES ( null";
// Die Variablen kommen in der Reihenfolge Tabellenname, 1. Feld, ...,letztes Feld
// Deshalb in der Schleife das erste Feld 'Tabelle' ignorieren
$_select = "SELECT * FROM ";
foreach( $HTTP_POST_VARS as $k=>$elem )
{
  if( $k == "Tabelle" )
    continue;
  if(isset($debug) && $debug)
    echo "$k: $elem vom Typ ", gettype($elem), "<br>";
  $arr = explode( "_", $k );
  if( !isset($arr[1]) )
  {
    if(isset($debug) && $debug) echo"\nk $k : ohne _ ?!<p>";
    continue;
  }
  if( !strstr( $_select, $arr[0]) )
    $_select .= $arr[0] . " WHERE ";
  switch( $arr[1] )
  {
    case "date":
      unset($_a);
      $_a = explode( ".", $elem );
      if( isset($_a[2]) and 2 == strlen( $_a[2] ) )
        $_a[2] = "20" . $_a[2];
      if( isset($_a[2]) and 4 == strlen( $_a[2] ) )
        $datum = "$_a[2]-$_a[1]-$_a[0]";
      else
      {
        if( !isset($_a[2]) )
          $datum = $elem;
      }
      $sql .= ", '".$datum."'";
      $_select  .= "$arr[2] = '" . $elem . "' AND ";
    break;
    case "int":
      $sql .= ", $elem";
    break;
    case "real":
      unset( $aDP );
      $aDP = explode( ",", $elem );
      if( 1 < count($aDP) )
        $elem = "$aDP[0].$aDP[1]";
       $sql .= ", '$elem'";
    break;
    case "enum":
    case "string":
      $sql .= ", '".$elem."'";
      $_select  .= "$arr[2] = '" . $elem . "' AND ";
    break;
    case "time":
      $sql .= ", '".$elem."'";
    break;
    case "blob":
      $sql .= ", '".$elem."'";
    break;
    default:
      echo "unbekannter Datentyp $arr[1]<br>";
  }
}
$sql .= " )";
$_select = rtrim( $_select, " AND " );
if(isset($debug) && $debug)
{
  echo "$sql<br>";
  echo "$_select<br>";
}
$result = mysql_db_query( $MySQLDb, $sql );
if(!$result)
{
  $result = mysql_db_query( $MySQLDb, $_select );
  if($result)
  {
    ?>This record already exists. It must not be saved once more.<?php
    $arr = mysql_fetch_row( $result );
    $_eCandy[$_E['entitaet']] = $arr[0]; // damit wird auf die gerade angelegte Instanz in ihrer Liste positioniert
  }
  else
    reagierenAufSQLFehler( $lkid, $sql, $ID );
}
else
{
  echo "\nThe record is saved<br>";
  $_A['inserted'] = true;
  if( 0 )
  {
  include("linkFortsetzen.inc");
  lesenRETabelle( $result, $MySQLDb, $_E['entitaet'], "" );
  if( $result )
  {
    echo "\n<a name='{$_E['entitaet']}'></a>";
    echo "\n<hr><center><H1>{$_E['entitaet']}</H1>";

    spaltenNamenHolen( $result, $spaltenName );

    // --- Anzeige formatieren
    $auchIDausgeben = false;
    tabelleBeginnen();
    ausgebenAlsTabellenkopf( $spaltenName, $auchIDausgeben, $cSpalten, "", "", "" );
    //

    $fChecked = false;
    //$arrFeldTyp = range(0,-1);
    unset($arrFeldTyp);
    for( $z=0; $z<count($spaltenName); $z++ )	// wegen Datumsformatierung
      $arrFeldTyp[$z] = mysql_field_type( $result, $z );
    while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
    {
      tabellenZeileBeginnen();
      ausgebenAlsTabellenzeile( $row,	$auchIDausgeben, $fChecked, $_E['entitaet'], isset($globalID)?$globalID:0, $arrFeldTyp, $_E['entitaet'], isset($ActionSuffix)?$ActionSuffix:"", "", $dummy );
      tabellenZeileBeenden();
    }

    //
    tabelleBeenden();

    $succ = mysql_free_result( $result );
  }
  }
}
?>
