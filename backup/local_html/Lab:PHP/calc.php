<?php
    if(isset($_GET["val1"]) and isset($_GET["val2"])) {
        echo "<span><b>&nbsp;&nbsp;&nbsp;";
        
        if($_GET["val2"] ==! 0 and $_GET["oper"] !== 4) {
            $v1 = $_GET["val1"] + 0;
            $v2 = $_GET["val2"] + 0;
            if( (empty($v1) and $v1 ==! 0) or empty($v2)) {
                if($v2 === 0) {
                    echo "cannot divde by zero!";
                }
                else {
                    echo "please enter two values";
                }
            }
            else {
                $op = $_GET["oper"];
                switch($op) {
                    case 1:
                        echo $v1 + $v2;
                        break;
                    case 2:
                        echo $v1 - $v2;
                        break;
                    case 3:
                        echo $v1 * $v2;
                        break;
                    case 4:
                        echo $v1 / $v2;
                        break;
                    case 5:
                        echo $v1 % $v2;
                        break;
                    default:
                        echo "error inside... switch?";
                        break;

                }
            }
        }
        
        echo "</b></span>";
    }
?>