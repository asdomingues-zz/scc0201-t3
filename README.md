# Trabalho 3 - Base de dados

Programa capaz de gerenciar arquivos de dados como um banco de dados com inserção, busca e ordenação.
Além disso, inclui módulos para gerenciar índices para acelerar a busca e ordenação. 
Allan Silva Domingues | 10/09/15
---------------------------------------------------------------------------------------------------------
--Criadas e documentadas funções essenciais para o programa e de leitura do arquivo textual .schema.
ASD | 10/09/15 | 21:03
---------------------------------------------------------------------------------------------------------
--Criadas funções para ler e interpretar os arquivos de dados .data e criar os arquivos índice .idx.
ASD | 11/09/15 | 18:51
---------------------------------------------------------------------------------------------------------
--Criadas funções para impressão de inteiros, doubles e strings a partir de um void \*.
--Modificado o Makefile para facilitar testes.
--Adicionados novos .schema.
--Divididas as funções de ler arquivos (agora: uma função abre e outra lê).
--Criadas funções para imprimir os arquivos .schema, .data, .idx.
--Documentadas todas as novas funções.
ASD | 12/09/15 | 02:19
---------------------------------------------------------------------------------------------------------
--Criadas funções para comparar e trocar os campos nos índices.
--Criada a função para ordenar os índices.
--Criada a função para adicionar (append) um novo registro (com os campos do .schema) ao .data.
--Documentadas todas as novas funções.
ASD | 12/09/15 | 19:29
---------------------------------------------------------------------------------------------------------
--Criada funções para o comando select (busca em campos índice).
--Criada função para selecionar qual busca binária fazer e busca binária para inteiros.
--Documentadas todas as novas funções.
ASD | 13/09/15 | 13:13
---------------------------------------------------------------------------------------------------------
--Criadas funções para busca binária e sequencial.
--Documentadas as funções de busca.
--Adicionada a funcionalidade de atualizar o índice.
ASD | 19/09/15 | 00:26
---------------------------------------------------------------------------------------------------------
--Modificada a função de criar índices .idx para que não seja necessário ler o .data inteiro.
--Excluídas funções que só serviam para que a função de criar índices funcionasse.
--Adicionada uma função para obter a quantidade de arquivos do .data.
ASD | 19/09/15 | 10:04
---------------------------------------------------------------------------------------------------------
--Generalizadas as funções de busca e ordenação utilizando as funções de comparação.
--Modificadas as funções de comparação para ficarem mais simples.
--Redocumentadas as funções alteradas.
--Melhorias quanto a legibilidade do código.
ASD | 19/09/15 | 18:25
---------------------------------------------------------------------------------------------------------
