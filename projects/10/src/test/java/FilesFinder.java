import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Objects;

public class FilesFinder {

    public static File[] getFiles(String location) throws IOException, IllegalArgumentException {
        Path sourceLocation;
        ArrayList<File> jackFiles = new ArrayList<File>();

        sourceLocation = Paths.get(location);
        if(Files.notExists(sourceLocation)){
            throw new IllegalArgumentException("can not locate Nand2Tetris .jack file/s.");
        }
        if(!Files.isReadable(sourceLocation)){
            throw new IllegalArgumentException("Insufficient read privileges.");
        }

        //Check for path type
        if(Files.isRegularFile(sourceLocation)){
            if(!location.endsWith(".jack")){
                throw new IllegalArgumentException("File is not a valid Nand2Tetris .jack file.");
            }
            jackFiles.add(sourceLocation.toFile());
        }
        else if(Files.isDirectory(sourceLocation)){
            //collect all the .jack files in the directory.
            if(Objects.requireNonNull(sourceLocation.toFile().list()).length == 0){
                throw new IllegalArgumentException("The directory does not any Nand2Tetris .jack files.");
            }
            for(Path path : Files.list(sourceLocation).toArray(Path []::new)) {
                if(path.toString().endsWith(".jack")){
                    if(!Files.isReadable(path)){
                        throw new IllegalArgumentException(String.format("Access to a .jack file (%s) in directory is restricted.%n", path.getFileName()));
                    }
                    jackFiles.add(path.toFile());
                }
            }
        }
        else{
            throw new IllegalArgumentException("File type is unidentifiable.");
        }
        return (File[]) jackFiles.toArray();
    }
}
