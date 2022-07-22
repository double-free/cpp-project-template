# cpp-project-template

My cpp project template, with gcc docker build (arm64).

## Dependency

- docker

## Usage

1. build docker image (only once) with:

  ```console
docker build -t gcc-build ${repo_path}
```

2. run docker container with:

  ```console
./compile.sh
```
It mounts your current project directory to container `/app`.

3. build project in container

  ```console
cmake -DBUILD_TEST=on ../ && make -j8
```
