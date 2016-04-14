<?php
include ("fehler.inc");

// Verbinden zum MySQL-Server
function verbindenMitMySQLServer( &$lkid, $host, $user, $pw )
{
  $lkid = mysql_connect( $host, $user, $pw );
  if( !$lkid )
  {?>
    <h4>Datenbank ist nicht erreichbar?</h4>
    <ol>
      <li>Ist das Paket <em>php5-mysql</em> installiert?
    </ol>
    <?php
  }
  if( isset( $debug ) && $debug )
  {
    if( !$lkid )
      echo "Keine Verbindung zu MySQL möglich<br>Läuft der MySQL-Server?<br>";
    else
      echo "Geil, Verbindung zu MySQL ist möglich!<br>";
exit;
  }
  if( !$lkid )
  {
    /*if( isset( $_E['enableDbg'] ) )*/ exit;
?>
<script language=javascript type='text/javascript'>
  location.href = '/'
</script>
<?php
  }
  return $lkid;
}

// Datenbank wählen
function verbindenMitMySQLDB( &$succ, $db, $lkid )
{
  $succ = mysql_select_db( $db, $lkid);
  if( !$succ )
  {
    reagierenAufSQLFehler( $lkid, "Oeffnen von $db", $dummy );
    return $succ;
  }

  if( isset( $debug ) && $debug )
    echo "Datenbank ist offen (smile)<br>";

  return $succ;
}

?>
