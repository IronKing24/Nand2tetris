
import com.sun.net.httpserver.Authenticator;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.io.File;

import static org.junit.jupiter.api.Assertions.*;

class TokenizerTest {

    @Test
    void arrayTest(){
        String path = ClassLoader.getSystemResource("tests/ArrayTest").getPath().replace("%20", " ").substring(1);

        try{
            for (File f: FilesFinder.getFiles(path)) {
                Tokenizer tok = new Tokenizer(f);

                while(tok.hasMoreTokens()){

                }
            }
        }
        catch (Exception e){
            fail(e.getMessage());
        }
    }

    @Test
    void expressionLessTest(){
        try(Tokenizer tok = new Tokenizer(null)){

        }
        catch (Exception e){
            fail(e.getMessage());
        }
    }

    @Test
    void squareTest(){
        try(Tokenizer tok = new Tokenizer(null)){

        }
        catch (Exception e){
            fail(e.getMessage());
        }
    }
}
