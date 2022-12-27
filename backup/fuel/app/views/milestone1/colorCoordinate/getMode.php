<div class="jumbotron">
    <h1>Start your Color Coordinating Here!</h1>
    
    <div class="jumbo-decoration">
        <p>Fill out this short form declaring how many colors you wish to select from as well as the size of the output table. This will help us better provide a solution for your needs. Choose between up to 10 different color options and display an output table that has a size of anywhere between 1 and 26 rows/columns.</p>
        <br>
        <!-- changed action url and button type -->
        <form action="./colorCoordinate" method="get">
            <label for="rows">Number of colors:</label><br>
            <input type="number" min="1" max="10" id="rows" name="rows" value="1"><br>
            <label for="size">Size of output table:</label><br>
            <input type="number" min="1" max="26" id="size" name="size" value="1"><br><br>
            <input type="submit" id="firstFormButton">
        </form>
    </div>
</div>