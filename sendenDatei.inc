<?php
// Input: 
// $_E['rootDocuments']

if( isset($_REQUEST["preparedocC"]) )
  hiddenFeldSchreiben( "docC", $_REQUEST["preparedocC"] );

$debug = 0;
if( $debug ) echo "AuftragID, $AuftragID<br>BerichtNr $berichtNr<br>";
//Pfad (und Namen) einstellen, mit dem der Upload gespeichert werden soll:
//$str = $AuftragID . "-" . $berichtNr . ".odt";
$str = $_E['rootDocuments'];
?>
<ol>
<li>
1. Dr&uuml;cken Sie auf <em>Durchsuchen ...</em> und w&auml;hlen Sie in dem darauf folgenden Dialog ihre Datei aus:
</li>
<input type=file name=datei value=<?php echo $str;?>? size=80>
<li>
2. Senden Sie Ihre Datei ab:
<input type=submit value='senden'>
</li>
</ol>
