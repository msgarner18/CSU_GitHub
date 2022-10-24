echo "Profile A:"
mkdir a_dir
rm  -rf a_dir/*

cp profileA.jar a_dir

cd a_dir
jar xf profileA.jar
tree tf

cd ..

rm -rf a_dir

echo "Profile B..."
mkdir b_dir
rm -rf b_dir/*

cp profileB.jar b_dir

cd b_dir
jar xf profileB.jar
tree tf

cd ..
rm -rf b_dir
# jar xf b_dir/profileB.jar b_dir

# tree a_dir/tf
# tree b_dir/tf