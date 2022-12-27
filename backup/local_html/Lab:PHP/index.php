<!DOCTYPE html>
<html>
<body>
	<div id='main'>
        <!--TIP: Remove these comments to be able to view the code better--->
        <form method='POST'>
            <h2>Please input your favorite...</h2>
            <ul>
                <li>
                    <label for="bGame">Board Game</label>
                    <input type="text" name="bGame" id="bGame">
                </li>
                <li>
                    <label for="vGame">Video Game</label>
                    <input type="text" name="vGame" id="vGame">
                </li>
                <li>
                    <label for="mGenre">Music Genre</label>
                    <input type="text" name="mGenre" id="mGenre">
                </li>
                <li>
                    <label for="movie">Movie</label>
                    <input type="text" name="movie" id="movie">
                </li>
            </ul>
            <input type="submit" value="Submit">
            
            
        </form>

        <?php
            function isArraySet($arr) {
                $arrayIsSet = True;
                foreach($arr as $key) {
                    if(!isset($_POST[$key]) or empty($_POST[$key])) {
                        $arrayIsSet = False;
                    }
                }
                return $arrayIsSet;
            };

            $array = ["bGame", "vGame", "mGenre", "movie"];
            if(isArraySet($array)) {
                $bGame = $_POST['bGame'];
                $vGame = $_POST['vGame'];
                $mGenre = $_POST['mGenre'];
                $movie = $_POST['movie'];
                echo "
                    Board Game: $bGame<br>
                    Video Game: $vGame<br>
                    Music Genre: $mGenre<br>
                    Movie: $movie<br>
                ";
            } 
            else {
                echo "Please enter your information :(.";
            }
            
        ?>

        
	<div>
</body>
</html>