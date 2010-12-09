<?
function reagierenAufSQLFehler( $lkid, $sql, &$PKViolation )
{
global $AusgabeUnterdruecken;
	$fUnbekannterFehler = false;
	$errno = mysql_errno( $lkid );
	$errmsg = mysql_error( $lkid );
	$PKViolation = false;
	switch( $errno )
	{
		case 1062:
		     if( false == $AusgabeUnterdruecken )
			 echo "\nDieser Eintrag existiert bereits und darf kein weiteres mal abgelegt werden<br>";
		     $PKViolation=true;
		     break;
		case 1044:// Authentifizierungsproblem
?>
<script language=javascript type='text/javascript'>
location.href = './index.html'
</script>  
<?
		     break;
		default:
			$fUnbekannterFehler = true;
		     if( false == $AusgabeUnterdruecken )
		     {
//?>
//<script language=javascript type='text/javascript'>
//  location.href = '/'
//</script>
//<?
			echo "\nDie Anweisung '$sql' ging schief:<br>";
			echo "\nFehler Nr. $errno<br>";
			echo "\nFehlermeldung '$errmsg'";
		     }
			break;
	}
	if( $fUnbekannterFehler and false == $AusgabeUnterdruecken )
		echo "\n<h4>Verst&auml;ndigen Sie bitte Ihren Systemadministrator<br>";
}
?>
