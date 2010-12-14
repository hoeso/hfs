<center>
<?
/************ Input **********************************************************
 * $zielTabelle	: der Name der Zieltabelle
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

if( !isset($zielTabelle) and isset($mapTable) )
    $zielTabelle=$map[$mapTable];
if( false == isset($ActionSuffix) )
  $ActionSuffix="";

if( !isset($sql) and isset($zielTabelle) )
  {
    $sql = $Select[$zielTabelle];
    if ( isset($OrderBy[$zielTabelle]))
    {
      $sql .= $OrderBy[$zielTabelle];
      // die ORDER By -Klausel beginnt mit einem Space,
      // deshalb ist die Anfuegung so in Ordnung.
    }
  }
if( isset( $filterjahr ) )
{
  $order=" ORDER";
  $str=str_replace( "#filterjahr#", $filterjahr, $filterJahr[$zielTabelle] );
  if( strstr( $sql, $order ) )
    $sql=str_replace( $order, $str . $order, $sql );
  else
    $sql .= $str;
}
if( !isset($zielTabelle) )
  $zielTabelle="";

anzeigen( $MySQLDb, $sql, $zielTabelle, $ActionSuffix );
?>
