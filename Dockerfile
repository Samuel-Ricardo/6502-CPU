# Use a base image with C++ development tools installed
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the source code into the container
COPY . .

# Compile the C++ program
RUN g++ src/main.cpp -o target/app

# Set the command to run when the container starts
CMD ["./target/app"]
