<?php

 // Limit requests to SSL only.
 if ( !function_exists('is_ssl') ) { function is_ssl() {
  if ( isset($_SERVER['HTTPS']) ) { if ( 'on' == strtolower($_SERVER['HTTPS']) ) return true;
  if ( '1' == $_SERVER['HTTPS'] ) return true; } elseif ( isset($_SERVER['SERVER_PORT']) && ( 443 == intval($_SERVER['SERVER_PORT']) ) ) return true; 
  return false;
 } }
 if ( !is_ssl() ) { // The following block is used to restrict access to the insecure version, and bump users to the secure one.
  echo 'Access denied to insecure request from '.$_SERVER['REMOTE_ADDR']; die;
 }

  // HTTPS requests made to this php script will go through Galvanic.

  function our_json_encode($a,$loose=FALSE) {
   if ( $loose === FALSE )
   $o= json_encode($a, JSON_PRESERVE_ZERO_FRACTION/* | JSON_INVALID_UTF8_SUBSTITUTE in 7.2*/, 512);
   else
   $o= json_encode($a, JSON_PRESERVE_ZERO_FRACTION | JSON_PARTIAL_OUTPUT_ON_ERROR /* | JSON_INVALID_UTF8_SUBSTITUTE in 7.2*/, 512 );
   $e=json_last_error();
   switch ( $e ) {
    case JSON_ERROR_NONE: return $o;
    case JSON_ERROR_DEPTH: return 'JSON_ERROR_DEPTH';
    case JSON_ERROR_STATE_MISMATCH: return 'JSON_ERROR_STATE_MISMATCH';
    case JSON_ERROR_CTRL_CHAR: return 'JSON_ERROR_CTRL_CHAR';
    case JSON_ERROR_SYNTAX: return 'JSON_ERROR_SYNTAX';
    case JSON_ERROR_UTF8: return 'JSON_ERROR_UTF8';
    case JSON_ERROR_RECURSION: return 'JSON_ERROR_RECURSION';
    case JSON_ERROR_INF_OR_NAN: return 'JSON_ERROR_INF_OR_NAN';
    case JSON_ERROR_UNSUPPORTED_TYPE: return 'JSON_ERROR_UNSUPPORTED_TYPE';
    case JSON_ERROR_INVALID_PROPERTY_NAME: return 'JSON_ERROR_INVALID_PROPERTY_NAME';
    case JSON_ERROR_UTF16: return 'JSON_ERROR_UTF16';
   }
  }

  $json = array(
   "cookies" => $_COOKIE,
   "get" => $_GET,
   "post" => $_POST
  );

  $outfile=$tempnam("/tmp","galvanic");
  file_put_contents($outfile,our_json_encode($json));
  echo exec("../framework/Galvanic php request=$outfile");
