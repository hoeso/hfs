<?
/************ Input **********************************************************
 * $_E['entitaet']	: der Name der Zieltabelle
 * $mapTable	: falls der Name der Zieltabelle leer ist
 * $sql		: selektiert den gewuenschten Inhalt
 *****************************************************************************/
//$sql=str_replace( "\$gNLID", $gNLID, $sql );
// wg. PHP4 (5 stoert ein \ im String nicht )

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

if( !isset($sql) and isset($_E['entitaet']) )
  {
    $sql = $Select[$_E['entitaet']];
    if ( isset($OrderBy[$_E['entitaet']]))
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

anzeigen( $MySQLDb, $sql, $_E['entitaet'], $ActionSuffix );
?>
