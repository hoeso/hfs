<?php
define("MYSQL_ASSOC", MYSQLI_ASSOC);
define("MYSQL_NUM", MYSQLI_NUM);

if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
$_E['host'] = "";
$_E['user'] = "";
$_E['pw'] = "";
$_E['mysql'] = "";
/***
 *** Diese Funktion gibt es nicht mehr
 ***/
function mysql_connect( $host, $user, $pw )
{
  global $_E;
  
  $_E['host'] = $host;
  $_E['user'] = $user;
  $_E['pw'] = $pw;
  
  return 1; // dummy-handle
}

///////
function mysql_select_db( $db, $lkid)
{
  global $_E;
  global $b_;
  if( isset($_REQUEST["d"]) )
    dEcho( $b_, "connect mit " . $_E['host'] . $_E['user'] . $_E['pw'] . $db );

  $_E['mysql'] = mysqli_connect( $_E['host'], $_E['user'], $_E['pw'], $db );
  if (mysqli_connect_errno())
  {
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
    return false;
  }
  return true;
}

///////
function mysql_db_query( $db, $sql )
{
  global $_E;
  mysqli_select_db( $_E['mysql'], $db );
  $result = mysqli_query( $_E['mysql'], $sql );
  if( !$result )
    echo "db_query: Fehler No. " . mysqli_errno( $_E['mysql'] ) . " bei Befehl " . $sql . "<br>";
  return $result;
}

///////
function mysql_list_fields( $db, $table, $lkid )
{
  global $_E;
  global $b_;
  // $result zurueckgeben:
  if( isset($_REQUEST["d"]) )
    dEcho( $b_, "SHOW COLUMNS FROM " . $table );
  //return mysqli_query( $_E['mysql'], "SHOW COLUMNS FROM " . $table, MYSQLI_STORE_RESULT );
  return mysqli_query( $_E['mysql'], "SELECT * FROM " . $table . " LIMIT 1", MYSQLI_STORE_RESULT );
}

///////
function mysql_num_fields( $result )
{
  return mysqli_num_fields( $result );
}

///////
function mysql_num_rows( $result )
{
  return mysqli_num_rows( $result );
}

///////
function mysql_fetch_array( $result, $style )
{
  return mysqli_fetch_array( $result, $style );
}

///////
function mysql_free_result( $result )
{
  mysqli_free_result( $result );
}

///////
function mysql_fetch_row( $result )
{
  return mysqli_fetch_row( $result );
}

///////
function mysql_field_name( $result, $i )
{
  $finfo = mysqli_fetch_field_direct( $result, $i );
  return $finfo->name;
}

///////
function mysql_field_type( $result, $i )
{
  global $b_;
    
  $finfo = mysqli_fetch_field_direct( $result, $i );
  if( isset($_REQUEST["d"]) )
  {
    dEcho( $b_, "Feld-Name: " . $finfo->name . "; Feld-Typ: " . $finfo-Type );
  }
  switch( $finfo->type )
  {
    case MYSQLI_TYPE_VAR_STRING:
      return "string";
    case MYSQLI_TYPE_STRING:
      if( 257 == $finfo->flags )
        return "enum";
      else
        return "string";
    case MYSQLI_TYPE_DATE:
      return "date";
    case MYSQLI_TYPE_TIME:
      return "time";
    case MYSQLI_TYPE_NEWDECIMAL:
      return "decimal";
    case MYSQLI_TYPE_BLOB:
      return "blob";
    default:
      //echo $finfo->type . "<br>";
      break;
  }
}

///////
function mysql_field_flags( $result, $i )
{
  global $b_;
  $finfo = mysqli_fetch_field_direct( $result, $i );
  
  //return $finfo->flags;
  switch( $finfo->type )
  {
    case 10:
    return "date";
    case 3:
    return "int";
    case MYSQLI_TYPE_BLOB:
    return "blob";
    case 246:
    return "real";
    case MYSQLI_TYPE_VAR_STRING:
    return "string";
    case MYSQLI_TYPE_STRING:
      //if( 256 == $finfo->flags || 257 == $finfo->flags )
      if( ($finfo->flags | MYSQLI_ENUM_FLAG) || ($finfo->flags | 257) )
        return "enum";
      else
        return "string";
  }
  if( isset($_REQUEST["d"]) )
  {
    dEcho( $b_, "Type-Flag " . $finfo->type . " wurde nicht erkannt" );
    printf("Name:     %s\n", $finfo->name);
    printf("Table:    %s\n", $finfo->table);
    printf("max. Len: %d\n", $finfo->max_length);
    printf("Flags:    %d\n", $finfo->flags);
    printf("Type:     %d\n", $finfo->type);
  }
  return "nicht erkannt";
}

function mysql_close( $lkid )
{
  global $_E;
  mysqli_close ( $_E['mysql'] );
}

///////
function mysql_fetch_field( $result, $i )
{
  for( $j=0; $j < $i; $j++ )
    $finfo = mysqli_fetch_field( $result );
  var_dump($finfo);
  return $finfo;
}

///////
function mysql_errno( $lkid )
{
  return mysqli_errno( $_E['mysql'] );
}

///////
function mysql_error( $lkid )
{
  return mysqli_error( $_E['mysql'] );
}
?>
