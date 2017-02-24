<?php
$objekt=$table;
if( "nein" == $wert )
    $val="ja";
else if( "ja" == $wert )
    $val="nein";
$sql="UPDATE $table SET $feld='$val' WHERE ID=$ID";
//echo $sql; exit;
$result = mysql_db_query( $MySQLDb, $sql );
if(!$result)
{
	reagierenAufSQLFehler( $lkid, $sql, $ID );
	exit;
}

$goto=true;//dann wird gleich wieder zurueckgesprungen mittels javascript
?>
