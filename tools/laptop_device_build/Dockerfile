FROM ubuntu:24.04

ARG CAPNP_VERSION=1.0.1

ENV PYTHONUNBUFFERED=1
ENV UV_LINK_MODE=copy
WORKDIR /work

# AGNOS 17.2 uses the Ubuntu 24.04 / Python 3.12 ABI. Application/native
# dependency versions come from Sunnypilot's frozen uv.lock, not StarPilot's
# current base image. This container runs natively on the ARM GitHub runner.
# rsync/ssh-client are needed for optional sysroot sync from a comma device.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    build-essential \
    clang \
    llvm \
    libomp-dev \
    rsync \
    openssh-client \
    e2fsprogs \
    android-sdk-libsparse-utils \
    qemu-user-static \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    cmake \
    python3-pip \
    python3-dev \
    python3-venv \
    libegl1 \
    libgles2 \
    libgl1 \
    libgbm1 \
    libdrm2 \
    libx11-6 \
    libxrandr2 \
    libxinerama1 \
    libxcursor1 \
    libxi6 \
    xz-utils \
    git \
  && rm -rf /var/lib/apt/lists/*

RUN set -eux; \
    tmpdir="$(mktemp -d)"; \
    curl -fsSL "https://github.com/capnproto/capnproto/archive/refs/tags/v${CAPNP_VERSION}.tar.gz" | tar -xz -C "${tmpdir}"; \
    cmake -S "${tmpdir}/capnproto-${CAPNP_VERSION}/c++" -B "${tmpdir}/build" \
      -DBUILD_TESTING=OFF \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr/local; \
    cmake --build "${tmpdir}/build" -j"$(nproc)"; \
    cmake --install "${tmpdir}/build"; \
    ldconfig; \
    capnp --version; \
    rm -rf "${tmpdir}"

RUN /usr/bin/python3 -m pip install --no-cache-dir --break-system-packages uv

# Fix for "dubious ownership" git errors when mounting folders on Linux hosts.
RUN git config --global --add safe.directory /work
