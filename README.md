# torre-de-hanoi-C
Programa em C para resolução do quebra-cabeça da **Torre de Hanoi**.  
Diferente de outros programas com objetivos iguais, esse foi criado de forma a resolver o quebra-cabeça com um número qualquer de discos e uma distribuição inicial de peças. Bem, isso contanto que essa distribuição siga as regras padrão da **Torre de Hanoi**.

Esse programa foi criado para uma *atividade avaliativa durante minha gradução em bacharelado no curso de **Sistema de Informação**.*


Caso você vá usar esse programa, é importante saber que apenas apertar um botão no compilador para rodar a *main* não irá funcionar.  
Para rodar esse programa de forma apropriada, você precisará do ***Makefile***.

Primeiro, na pasta do projeto, rode o comando **`make build`** no terminal para compilar o projeto;  
Então, com o programa compilado, rode o comando **`make run`** para executá-lo.  
Para remover os arquivos criados durante a compilação, rode o comando **`make clean`**.  
Você também pode rodar apenas o comando **`make`** para compilar e iniciar o programa de uma vez.

**ATENÇÃO:** Caso você faça alguma alteração no código, você vai precisar recompilar ele para que elas afetem o programa.



Caso você esteja se perguntando se a resolução é a melhor possível, a resposta é: "Depende".  
Já que a entrada de dados é customizada, o que te permite rodar o progama com os discos todos embalharados, a solução fica mais complicada.  
Eu não criei uma super inteligência artifical capaz de aprender e se adaptar a qualquer situação.  
Embora eu tenha tentando bastante reduzir o número de movimentos gastos para resolver um problema, não ficou perfeito.  
Dependendo de como for a entrada de dados, o programa pode resolver com o menor número de movimentos possível;  
Mas e a os discos estiverem bastante embaralhados no inicio, a 'melhor solução' pode estar acima da inteligẽncia do meu código.