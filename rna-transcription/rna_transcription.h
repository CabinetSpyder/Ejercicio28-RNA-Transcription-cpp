#if !defined(RNA_TRANSCRIPTION_H)
#define RNA_TRANSCRIPTION_H

#include <string>
#include <map>
#include <type_traits> // para std::is_same_v
#include <stdexcept> //Para std::invalid_argument


namespace rna_transcription {

    template <typename T>
    T to_rna(T dna_strand){
        
        std::map<char, char> dna_to_rna_conversion{{'G', 'C'}, {'C', 'G'}, {'T', 'A'}, {'A', 'U'}};
        
        if constexpr(std::is_same_v<T, char>){ //con constexpr verificamos en tiempo de compilacion que T sea de tipo char, si no lo es, no compila
            if(dna_to_rna_conversion.find(dna_strand) != dna_to_rna_conversion.end()){
                return dna_to_rna_conversion[dna_strand];             
            }
            //No es necesario para los tests pero podemos lanzar una excepcion
            throw std::invalid_argument("Invalid protein");

        }else if constexpr(std::is_same_v<T, std::string>){
            T rna;
            for(auto ch : dna_strand){
                if(dna_to_rna_conversion.find(ch) != dna_to_rna_conversion.end()){
                    
                    rna += dna_to_rna_conversion[ch];
                }
                //No es necesario para los tests pero podemos lanzar una excepcion
                throw std::invalid_argument("Invalid DNA strand");
            }
            return rna.c_str(); // // Devolvemos el puntero al contenido de la cadena. Para pasar el ultimo test

        }else if constexpr (std::is_same_v<T, const char*>) { // Si es un const char* (por defecto es un puntero a cadena)
            return to_rna<std::string>(std::string(dna_strand)); // Convertimos a std::string y lo pasamos
        
        }else {
            static_assert(std::is_same_v<T, std::string> || std::is_same_v<T, char> || std::is_same_v<T, const char*>,
                          "Unsupported type for to_rna(). Only char, std::string, or const char* are allowed.");
        }

    }//End template

}  // namespace rna_transcription

#endif // RNA_TRANSCRIPTION_H