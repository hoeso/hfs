<?
if( !isset($suffixA) )
  $suffixA="";
$fDatum = lesenRETabelle( $result, $MySQLDb, $_E['entitaetLinks'], $suffixA );
if( !$result )
{
  if( isset($debug) and $debug )
    echo "Ist die Tabelle '$table' leer?<br>";
  return;
}
if( isset($debug) && $debug )
  echo "ausgeben der Tabelle '{$_E['entitaetLinks']}' ...<br>";

?><table>
<tr>
<th><?
echo $_E['entitaetLinks'];
?></th>
<th><?
echo $_E['entitaetRechts'];
?></th>
<th></th>
</tr><?
if( isset($fUpdateB) )
  $str="&fUpdateB=$fUpdateB";
else
  $str="";
?><form action="./mn.php?mn=4454<?
echo $str;
?>" method='post'>
<input type='hidden' name='TabelleM' value='<?
echo $_E['entitaet'];
?>'>
<tr>
<td><?
ListeMitID( $result, 'A', $_E['entitaetLinks'], $fDatum, isset($anzuzeigen)?$anzuzeigen:"" );
?></td><?
$succ = mysql_free_result( $result );

$fDatum = lesenRETabelle( $result, $MySQLDb, $_E['entitaetRechts'], "" );
if( $result )
{
  ?><td><?
  ListeMitID( $result, 'B', $_E['entitaetRechts'], $fDatum, isset($anzuzeigen)?$anzuzeigen:"" );
  ?></td><?
  $succ = mysql_free_result( $result );
}
?><td>
<input type='submit' value='zuordnen'>
</td></tr>
</form>
</table><?

if( isset($Select[$_E['entitaet']]) )
  $sql = $Select[$_E['entitaet']];
if( isset($OrderBy[$_E['entitaet']]) && isset($sql) )
    $sql .= $OrderBy[$_E['entitaet']];
$zielTabelle=$_E['entitaet'];
?>
