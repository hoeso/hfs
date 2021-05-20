<?php
if( isset($strSubmitLabel) )
    $value=$strSubmitLabel;
else if( $zielTabelle )
    $value="speichern";
else
    $value="weiter >>";

if( !isset($keinInsert) or false == $keinInsert )
{
  ?><input type='submit' id='submit' value='<?php
  echo $value;
  ?>'><?php
}
if( isset($fMailenAuftrag) and true == $fMailenAuftrag and "specht" != $user )
{
?>
<p align=left>
<?php
	$fChecked = true;
 $today = getdate();
 $zeitstempel=$today['year'] . "." . $today['mon'] . "." . $today['mday'] . "." . $today['hours'] . "_" . $today['minutes'] . "_" . $today['seconds'];
	formularAuswahlfeldSchreiben( "als eMail versenden", "rechts", "checkbox", false, "teeFile", "download/$zeitstempel.auftrag$PHPSESSID.html" );
	hiddenFeldSchreiben( "subject", "Beauftragung" );
}
?>
</td>
</tr>
</FORM>
<?php
if( !isset($keinInsert) or false == $keinInsert )
{
  if( $zielTabelle )
  {
?>
<script language=javascript type='text/javascript'>
<!--
<?php
    if( isset($focusName) and $focusName )
	   echo"\ndocument.frm$zielTabelle.$focusName.focus()\n";
?>
// -->
</script>
<?php
  }
 echo "\n</table>";
}

if( isset($zielTabelle) and isset($Select[$zielTabelle]) )
  $sql = $Select[$zielTabelle];
else
  $sql = "";
// womit werden die Treffer eindeutig identifiziert?

if( isset($SelNurPK) and $SelNurPK )
{
	$sql .= " and ";
	if( isset($TabellePK) and $TabellePK )
	{
	    $sql .= $TabellePK;
	    $sql .= "ID=" . $PK;
	}
	else
	{
		$sql .= $globalTab;
	    $sql .= "ID=" . $globalID;
	}
}
if( isset($nochnFilter) and $nochnFilter )
{
	$nochnFilter=str_replace( "%20", " ", $nochnFilter );
	$nochnFilter=str_replace( "\$gNLID", $gNLID, $nochnFilter );
	$sql .= " $nochnFilter";
}
if( isset($AND) and $AND )
    $sql .= $AND;
if( isset($_E["filter"]) and !isset($_A['filterDone']) )
  $sql .= $_E["filter"]; // zB gesetzt in pruefendSymbol.prj
if( isset($OrderBy[$zielTabelle]) )
    $sql .= $OrderBy[$zielTabelle];

if( isset($nochnFilter) and $nochnFilter )
    $zielTabelle="ohne submit Knopf";
?>
