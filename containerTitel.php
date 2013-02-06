<h2>
<?
if( isset($_eTitel[0]) )
{
  echo $_eTitel[0]; // 1. Titel anzeigen
  array_splice($_eTitel, 0, 1); // zum naechsten Titel schalten
}
?>
</h2>