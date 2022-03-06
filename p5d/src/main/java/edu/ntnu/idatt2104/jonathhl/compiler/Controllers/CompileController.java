package edu.ntnu.idatt2104.jonathhl.compiler.Controllers;

import java.util.Map;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin
public class CompileController {
    
    @PostMapping("/comp")
    public String compile(@RequestBody Map<String, String> code) {

        // TODO: Fix return value
        return null;
    }
}
