<?php
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
function reagierenAufSQLFehler( $lkid, $sql, &$PKViolation )
{
  global $AusgabeUnterdruecken;
  global $_eCandy;
  $fUnbekannterFehler = false;
  $errno = mysql_errno( $lkid );
  $errmsg = mysql_error( $lkid );
  $PKViolation = false;
  if( isset($_REQUEST["d"]) )
    dEcho( $b_, "errno: " . $errno );
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
      <?php
    break;
    default:
      $fUnbekannterFehler = true;
      if( false == $AusgabeUnterdruecken )
      {
	if( isset($_REQUEST['zielTabelle']) )
	{
	  echo "\n$_REQUEST[zielTabelle]: ";
	  if( isset($_eCandy) and isset($_eCandy[$_REQUEST['zielTabelle']]) and !$_eCandy[$_REQUEST['zielTabelle']] )
	    $_eCandy[$_REQUEST['zielTabelle']] = 1;
	}
	?><!-- Could it be this entry does already exist?<br--><?php
      }
    break;
  }
  //if( $fUnbekannterFehler and false == $AusgabeUnterdruecken )
    //echo "\n<h4>Verst&auml;ndigen Sie bitte Ihren Systemadministrator<br>";
}
?>
