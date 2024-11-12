<h1 align="center">Projeto da Tarefa Prática: Estudo Visual</h1>
<p align="center">Curso de Análise e Desenvolvimento de Sistemas - EAD</p>

**Objetivo do Projeto**

O **Projeto de Estudo Visual** foi desenvolvido com o objetivo de criar uma plataforma interativa que ajude no aprendizado de diferentes áreas do conhecimento, com ênfase inicial em geografia. O sistema utiliza flashcards personalizados para facilitar o estudo de conteúdos visuais, como bandeiras de países. A ideia é permitir que os usuários criem seus próprios flashcards com imagens e textos, promovendo um estudo mais dinâmico e visual.

O sistema foi projetado para ser simples, atendendo tanto a estudantes quanto professores que buscam uma maneira personalizada de aprender e ensinar. O "Estudo Visual" permite criar, listar, editar, deletar, salvar, carregar e buscar flashcards, com suporte para imagens associadas a cada item, de maneira prática e intuitiva.

**Estrutura do Sistema e Implementação**

A estrutura de dados principal é composta por duas structs: Categoria e Flashcard, que são usadas para organizar e armazenar as informações dos flashcards.

**Categoria**: Cada categoria contém um nome e uma lista de flashcards associados a ela. As categorias ajudam a organizar os flashcards de forma lógica, permitindo ao usuário agrupar os materiais de estudo por temas.

**Flashcard**: Cada flashcard contém um título, uma descrição e o caminho para a imagem associada. As imagens são carregadas externamente pelo Electron para exibição no formato visual desejado.

A manipulação dos dados é feita utilizando arquivos CSV, que são lidos e gravados para garantir que as informações dos flashcards sejam persistidas. O sistema permite salvar novos dados, carregar dados existentes e realizar operações de busca para facilitar a navegação.

**Criação de Design com HTML e Electron**

Uma parte importante do sistema é a geração de um design visual, embora o sistema tenha sido desenvolvido com uma interface em linha de comando (CMD), a exibição das imagens associadas aos flashcards é realizada através do Electron. 

A função criarDesign() é responsável por gerar um arquivo HTML que inclui o layout dos flashcards e suas imagens, tornando a visualização mais agradável para o usuário. O Electron então carrega esse arquivo HTML e exibe o conteúdo de forma eficiente.

**Operações de Manipulação de Dados**

As operações de **criar**, **listar**, **deletar**, **editar**, **salvar**, **carregar** e **buscar** são essenciais para o funcionamento do sistema e são tratadas da seguinte maneira:

**Criar**: Ao criar uma nova categoria ou flashcard, o usuário fornece as informações necessárias, e o sistema cria uma nova entrada na memória. A memória é alocada dinamicamente, permitindo que o número de categorias e flashcards seja expandido conforme necessário.

**Listar**: O sistema exibe todos os flashcards ou categorias salvos, permitindo ao usuário visualizar rapidamente o que foi registrado. A lista é carregada diretamente do arquivo CSV, proporcionando um acesso rápido aos dados.

**Deletar**: O usuário pode excluir categorias ou flashcards, o que implica na remoção dos dados da memória e da base de dados (arquivo CSV).

**Editar**: Quando um flashcard precisa ser alterado, o sistema permite que o título, a descrição ou a imagem sejam atualizados. Após a edição, as mudanças são refletidas no arquivo CSV.

**Salvar e Carregar**: As funções **salvar()** e **carregar()** garantem que os dados sejam persistidos em arquivos CSV. O processo de salvar envolve escrever os dados dos flashcards em um arquivo de texto, enquanto o processo de carregar lê esses dados para que o sistema possa recuperá-los.

**Buscar**: A busca é realizada pelo título ou descrição dos flashcards. A função de busca percorre os dados carregados e retorna os itens que correspondem ao critério de pesquisa, facilitando a localização de flashcards específicos.

Isso permite que os usuários vejam as imagens de forma clara e nítida, sem a necessidade de um ambiente gráfico complexo no código base. 

**Conclusão**

O "Estudo Visual" é uma plataforma educacional simples que utiliza flashcards personalizados para tornar o aprendizado mais visual e interativo. Com a capacidade de criar, listar, editar, deletar, salvar, carregar e buscar flashcards, o sistema oferece uma solução prática e eficiente para estudantes e educadores. A utilização do Electron para exibição das imagens adiciona um toque visual ao sistema, sem complicar a implementação.

A implementação em CMD e a utilização do Electron para a parte visual tornam o sistema acessível e fácil de usar, atendendo às necessidades de personalização de conteúdos de estudo por meio de imagens e textos.

> **Status do projeto:** Finalizado

> **Requisitos**: https://nodejs.org/pt/download/source-code

## 👥 Equipe de Desenvolvimento

| [<img src="https://avatars.githubusercontent.com/u/88627696?v=4" width=100><br><strong>Caique Moura</strong></a>](https://github.com/Hideke) | [<img src="https://avatars.githubusercontent.com/u/106976173?v=4" width=100><br><strong>Cauã Nunes</strong></a>](https://github.com/Nun3s01) | [<img src="https://avatars.githubusercontent.com/u/183748742?v=4" width=100><br><strong>Luis Otávio</strong></a>](https://github.com/Luisgb07) | [<img src="https://avatars.githubusercontent.com/u/169729766?v=4" width=100><br><strong>Cauan Gomes</strong></a>](https://github.com/CauanGl) | [<img src="https://avatars.githubusercontent.com/u/167493219?v=4" width=100><br><strong>Nicholas Rosa</strong></a>](https://github.com/NicholasSarachini) | [<img src="https://avatars.githubusercontent.com/u/186329418?v=4" width=100><br><strong>Luis Resende</strong></a>](https://github.com/luisresende77) |
| :---: | :---: | :---: | :---: | :---: | :---: |
