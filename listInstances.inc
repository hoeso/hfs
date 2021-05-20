<?php
/************ Input **********************************************************
 * $_E['entitaet']	: der Name der Zieltabelle
 * $mapTable	: falls der Name der Zieltabelle leer ist
 * $sql		: selektiert den gewuenschten Inhalt
 *****************************************************************************/
//$sql=str_replace( "\$gNLID", $gNLID, $sql );
// wg. PHP4 (5 stoert ein \ im String nicht )

if( isset($_E["sql"]) )
{
  $sql = $_E["sql"]; // gesetzt zB in mn.prj case 't'
  if( isset($_E["filter"]) )
    $sql .= $_E["filter"];
  if( isset($_E["sort"]) )
    $sql .= $_E["sort"];
}
else if( isset($_A['sql']) ) // ueberstimmt den ungeschuetzten $sql
  $sql = $_A['sql'];
if ( isset($sql))
{
  $sql=str_replace( "\\", "", $sql );
}
$map = array(
	"Begehung"=>"Auftrag",
);

if( !isset($_E['entitaet']) and isset($mapTable) )
    $_E['entitaet']=$map[$mapTable];
if( false == isset($ActionSuffix) )
  $ActionSuffix="";

if( !isset($sql) and isset($_E['entitaet']) and isset($Select[$_E['entitaet']]) )
{
  $sql = $Select[$_E['entitaet']];
  if( isset($_E["sort"]) )
    $sql .= $_E["sort"];
  else if ( isset($OrderBy[$_E['entitaet']]))
  {
    $sql .= $OrderBy[$_E['entitaet']];
    // die ORDER By -Klausel beginnt mit einem Space,
    // deshalb ist die Anfuegung so in Ordnung.
  }
}
if( isset( $filterjahr ) )
{
  $order=" ORDER";
  $str=str_replace( "#filterjahr#", $filterjahr, $filterJahr[$_E['entitaet']] );
  if( strstr( $sql, $order ) )
    $sql=str_replace( $order, $str . $order, $sql );
  else
    $sql .= $str;
}
if( !isset($zielTabelle) )
  $zielTabelle="";
if( isset($_E) and !isset($_E['TabHeader']) )
  $fHeader=true;
else
  $fHeader=false;

anzeigen( $MySQLDb, isset($sql)?$sql:"SELECT 1, 'SELECT Anweisung fuer Entitaet $zielTabelle noch hinterlegen bitte in Modul sichten.prj'", isset($_E['entitaet'])?$_E['entitaet']:"", $ActionSuffix, $fHeader );
?>
