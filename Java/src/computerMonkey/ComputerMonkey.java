package computerMonkey;
import java.util.Random;

public class ComputerMonkey {
	private String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	private Random random = new Random();

	// O score é calculado de acordo com a semelhança entre a string e a frase
	private int score(String string, String phrase){ 
		  int score = 0;
		  for(int i = 0; i< phrase.length(); i++){ 
			  if(string.charAt(i) == phrase.charAt(i)){
				  score += 1;
			  }
		  }
		  return score;	
		}
	
	// Gera uma sequencia aleatoria de letras com espaço
	private String generateRandomSequence(int tam){
		String randomSequence= "";
		for (int j = 0; j<tam; j++) {
			int randomIndexLetter = random.nextInt(letters.length()); 
			randomSequence += String.valueOf(letters.charAt(randomIndexLetter));
		  }
		  return randomSequence;
	}
	
		
	public void tryWrite(String phrase){
		//Gera a primeira frase aleatoria
		String baseString = generateRandomSequence(phrase.length());
		int interation = 0;

		System.out.println(String.format("Iteration: %d, %s, score:%d ", interation, baseString, score(baseString, phrase))+"\n");

		//Loop principal, se repete enquanto a frase não é igual
		while(!baseString.equals(phrase)){
			interation += 1;
			String[] listAux = new String[phrase.length()];
			String[] stringList = new String[100];
			
			for( String str : stringList){
				str = baseString;
			}

			// faz 100 copias da String
			for(int i = 0; i< stringList.length; i++){
				for(int letter = 0; letter < baseString.length() ; letter++){
					listAux[letter] = String.valueOf(baseString.charAt(letter));
				}
				
				for(int j = 0; j<listAux.length; j++){
					//Chance de 5% de mutação
					if(Math.random() >= 0.95){
						int randomIndexLetter = random.nextInt(letters.length());
						listAux[j] = String.valueOf(letters.charAt(randomIndexLetter));
					}
			
				String stringAux = String.join("", listAux);
				//Compara se a frase gerada é mais parecida com a frase alvo se for mantém as mudanças.
				if(score(stringAux, phrase) > score(baseString, phrase)){
					baseString = stringAux;
				}
				}
			}
		System.out.println(String.format("Iteration: %d, %s, score:%d ", interation, baseString, score(baseString, phrase)));
		}
	}

}
