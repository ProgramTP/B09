// Convert folder structure Year/coursecode to coursecode/year
tgt="$2"
src="$1"
if [ "$#" -ne 2 ]; then
    echo "Enter two arguments"
    exit 1
fi
if [ -d "$tgt" ]; then
    echo "target exists"
    exit 2
fi
mkdir "$tgt"

createDir(){
    for i in "$1"/* ; do
        for j in "$i"/* ; do
            x=`basename "$j"`
            y=`basename "$i"`
            cd "$tgt"
	    if [ ! -d "$tgt"/"$x"/* ]; then
                mkdir "$x"
	    fi
            cd "$x"
            mkdir "$y"
            cd ..
            cd ..
            cp -R "$src"/"$y"/"$x"/* "$tgt"/"$x"/"$y"
        done
    done
}

createDir "$src"
