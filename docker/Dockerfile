FROM debian:latest

RUN apt-get update && apt-get -y install git vim procps file binutils tmux

RUN git clone https://github.com/tsiguenz/dotfiles.git
RUN cp dotfiles/vimrc /root/.vimrc
RUN cp dotfiles/tmux.conf /root/.tmux.conf
RUN rm -rf dotfiles

WORKDIR /src

ENTRYPOINT ["bash"]
