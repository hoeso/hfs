<?php
/************ Input **********************************************************
 * $_POST     	    : NEU seit PHP 5, es gibt kein $HTTP_POST_VARS mehr
 * 
 *****************************************************************************/
$HTTP_POST_VARS = $_POST;
if( isset($backupSELECTSL1) )
{
  if( isset($TabelleSL1) )
    $ActionSuffix = "&TabelleSL1=$TabelleSL1";
  if( isset($ActionSuffix) )
    $ActionSuffix .= "&backupSELECTSL1=$backupSELECTSL1";
	else
    $ActionSuffix = "&backupSELECTSL1=$backupSELECTSL1";
	  
}
$debug=0;
if( isset( $HTTP_POST_VARS ) )
{
  reset( $HTTP_POST_VARS );
  // Das 1. Feld ist immer der AUTOINKREMENT-Primaerschluessel
  $sql = "UPDATE {$_E['entitaet']} SET ";
  // Die Variablen kommen in der Reihenfolge Tabellenname, 1. Feld, ...,letztes Feld
  // Deshalb in der Schleife das erste Feld 'Tabelle' ignorieren
  foreach( $HTTP_POST_VARS as $k=>$elem )
  {
    if( $k == "ID" )
    {
      $_E['ID']=$elem;
      continue;
    }
    if( $k == "ID1" )
    {
      continue;
    }
    if($debug)
      echo "$k: $elem vom Typ ", gettype($elem), "<br>";
    $arr = explode( "_", $k );
    if( !strstr( $arr[1], "set" ) )
      $sql .="$arr[2]=";
    else if( !$fSet )
      $sql .="$arr[2]=";
    switch( $arr[1] )
    {
      case "blob":
        $sql .= "'$elem'";
      break;
      case "date":
        $arr = explode( ".", $elem );
        unset($datum);
        if( isset($arr[2]) and 4 == strlen( $arr[2] ) )
        {
          $datum = "$arr[2]-$arr[1]-$arr[0]";
          $sql .= "'$datum'";
        }
        else
          $sql .= "null";
        break;
      case "int":
        $sql .= "$elem";
      break;
      case "decimal":
      case "real":
        unset( $aDP );
        $aDP = explode( ",", $elem );
        if( 1 < count($aDP) )
          $elem = "$aDP[0].$aDP[1]";
        $sql .= "'$elem'";
      break;
      case "enum":
      case "string":
        $sql .= "'$elem'";
      break;
      case "time":
        $sql .= "'$elem'";
      break;
      case "set0":
        if( false == $fSet )
          $sql .= "'";
        $sql .= "$elem";
        $fSet = true;
      break;
      case "set1":
        if( false == $fSet )
          $sql .= "'";
        $sql .= "$elem";
        $fSet = true;
      break;
      case "set2":
        if( false == $fSet )
          $sql .= "'";
        $sql .= "$elem";
        $fSet = true;
      break;
      case "set3":
        if( false == $fSet )
          $sql .= "'";
        $sql .= "$elem";
        $fSet = true;
      break;
      case "set4":
        if( false == $fSet )
          $sql .= "'";
        $sql .= "$elem";
        $fSet = true;
      break;
      default:
        echo "unbekannter Datentyp $arr[1] von Feld $arr[2]<br>$sql";
        exit;
      break;
    }
    $sql .= ",";
  }
  $pos=strrpos($sql, ',');
  $sql = substr($sql, 0, $pos);
  if( isset($fSet) )
    $sql .= "'";
  if( $sql )
    $sql .= " WHERE ID={$_E['ID']}";
  else
    $sql = "SELECT NOW()";
//  echo "\n<!-- $sql -->";
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
  {
    reagierenAufSQLFehler( $lkid, $sql, $_E['ID'] );
  }
  else
  {
    ?>Der Eintrag wurde ge&auml;ndert<br><?php
    if( isset($Select[$_E['entitaet']]) )
    {
      $sql=$Select[$_E['entitaet']];
      if( strstr( $sql, "WHERE" ) )
        $sql .= " AND ";
      else
        $sql .= " WHERE ";
      if( !isset($sqlAbbrev[ $_E['entitaet'] ]) )
      {
        ?><p>... Referenzierung nicht m&ouml;glich.<br>
        Eintrag f&uuml;r <em><?php echo $_E['entitaet'];?></em> muss erg&auml;nzt werden in Modul entitySQLAbbrev.prj.<p><?php
        $_E['wZu']="anbietendKnopfZurueck";
        include("forkZu.inc");
      }
      $sql .= $sqlAbbrev[ $_E['entitaet'] ] . ".ID={$_E['ID']}";
      anzeigen( $MySQLDb, $sql, "ohne submit Knopf", isset($ActionSuffix)?$ActionSuffix:"" );
    }
  }
}
?>
