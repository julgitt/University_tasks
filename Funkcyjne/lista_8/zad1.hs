import Data.Char (toLower)
import System.IO (isEOF)
-- funkcja wykonuje operacje IO (efekt uboczny) i nie zwraca żadnej wartości
-- stan-aktualny stan strumienia wejścia, wprowadzona literka
-- kontekst: operacje wejścia/ wyjścia,
echoLower :: IO ()
echoLower = do
  eof <- isEOF
  if eof
    then return ()
    else do
      input <- getChar
      putChar (toLower input)
      echoLower

main :: IO ()
main = do
  putStrLn "Wpisz tekst:"
  echoLower
