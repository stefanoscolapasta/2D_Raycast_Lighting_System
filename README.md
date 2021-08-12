
<!-- PROJECT LOGO -->
<br />
<p align="center">

  <h1 align="center">Lighting Raycast System</h1>

  <p align="center">
    This is a simple lighting system based on raycasting and polygon triangulation, using SFML.
    <br />
    <br />
    <br />
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)


<!-- ABOUT THE PROJECT -->
## About The Project

This is an experimental project I'm working on to learn about Raycasting, Computer Graphics and OpenGl.
<br />
> To get a better grip on what polygon triangulation is and why it is important feel free to open the following links:
> <br />
> ![Polygon Triangulation](https://en.wikipedia.org/wiki/Polygon_triangulation)
> <br />
> ![Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)
<br />
It's also my first ever program/code written in C++. I do anyway realize the monstrosities I have writtend and how bad the source code is.
<br />
A total refactor of the project will be vital and non-postponable.
<br />
<br />
<br />
A demo of the lighting system.
<br />
<br />
![Raycast lighting](https://github.com/stefanoscolapasta/CppRayCastLightingSystem/blob/master/res/Demo.gif)
<br />
<br /><br />
Here I show how the raycasts are thrown and their contact points.
<br /><br />
![Raycast contact points](https://github.com/stefanoscolapasta/CppRayCastLightingSystem/blob/master/res/raycastsContactAndBoundary.gif)
<br />
<br /><br />
To be able to fill with colour a concave figure a form of triangulation is required, I decided to use the EarCut algorithm, a simple and fast polygon triangulation algorithm.
The result is not perfect, but can be improved.
<br /><br />
![Triangulation](https://github.com/stefanoscolapasta/CppRayCastLightingSystem/blob/master/res/triangulation.gif)
### Built With

* [C++](https://isocpp.org/)
* [SFML](https://www.sfml-dev.org/download.php)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.


### Prerequisites

You'll need to have SFML installed [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)


<!-- USAGE EXAMPLES -->
## Usage

Not interactive yet



<!-- ROADMAP -->
## Roadmap

- [ ] Rewriting source code in OOP
- [ ] Adding interactivity
- [ ] Adding shades blending



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE](https://github.com/zucchero-sintattico/Jhaturanga/blob/main/LICENSE) for more information.



<!-- CONTACT -->
## Contact


Project Link: [https://github.com/stefanoscolapasta/CppRayCastLightingSystem](https://github.com/stefanoscolapasta/CppRayCastLightingSystem)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [Stefano Scolari](https://www.linkedin.com/in/stefano-scolari-7a9440170/)



