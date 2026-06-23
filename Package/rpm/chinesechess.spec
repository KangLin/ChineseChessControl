# See: https://rpm-software-management.github.io/rpm/manual/spec.html

%define   INSTALL_PREFIX /opt/ChineseChess

Name:           chinesechess
Version:        2.0.14_dev
Release:        1%{?dist}
Summary:        Chinese chess

License:        GPL-3.0
URL:            https://github.com/KangLin/ChineseChessControl
Source0:        ChineseChess.tar.gz

Vendor:         Kang Lin <kl222@126.com>

BuildRequires: make git rpm-build rpmdevtools 
BuildRequires: gcc-c++
BuildRequires: automake autoconf libtool gettext gettext-autopoint
BuildRequires: cmake desktop-file-utils appstream curl wget
#BuildRequires: appstream

# Qt6
BuildRequires: qt6-qttools-devel qt6-qtbase-devel
BuildRequires: qt6-qt5compat-devel qt6-qtmultimedia-devel qt6-qtscxml-devel
BuildRequires: qt6-qtsvg-devel

%description
Chinese chess
Author: Kang Lin <kl222@126.com>

Donation:

https://github.com/KangLin/RabbitCommon/raw/master/Src/Resource/image/Contribute.png

https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute.png

https://gitlab.com/kl222/RabbitCommon/-/raw/master/Src/Resource/image/Contribute.png

# 预备参数
%prep
%setup -q -n ChineseChess

%generate_buildrequires

%build
echo "-- RPM_BUILD_DIR: $RPM_BUILD_DIR"
echo "-- RPM_BUILD_ROOT: $RPM_BUILD_ROOT"
echo "-- RPM_SOURCE_DIR: $RPM_SOURCE_DIR"
echo "-- RPM_SPECPARTS_DIR: $RPM_SPECPARTS_DIR"
echo "-- pwd: `pwd`"

cmake . -B $RPM_BUILD_DIR  \
    -DCMAKE_INSTALL_PREFIX=%{INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release \
    -DRabbitCommon_ROOT=${RabbitCommon_ROOT} \
    -DCMARK_SHARED=OFF \
    -DCMARK_TESTS=OFF \
    -DCMARK_STATIC=ON \
    -DWITH_CMARK=OFF \
    -DWITH_CMARK_GFM=ON \
    -DENABLE_UPDATE_TRANSLATIONS=ON \
    -DRABBIT_ENABLE_INSTALL_TARGETS=ON \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build $RPM_BUILD_DIR --config Release --parallel $(nproc)

%install
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component DependLibraries \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Runtime \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Plugin \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Application \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}

#if [ -n "${INSTALL_DIR}" ]; then
#    SOURCE_DIR=${INSTALL_DIR}%{_libdir}
#    DEST_DIR=${RPM_BUILD_ROOT}%{INSTALL_PREFIX}%{_libdir}
#    # 复制 .so 库文件及其符号链接
#    find $SOURCE_DIR -name "*.so*" -exec cp -d {} $DEST_DIR \;
#fi

# 安装前需要做的任务，如：创建用户
%pre

# 安装后需要做的任务 如：自动启动的任务
%post
INSTALL_PREFIX=/opt/ChineseChess
if [ ! -f /usr/share/applications/io.github.KangLin.ChineseChess.desktop ]; then
    if [ -f $INSTALL_PREFIX/share/applications/io.github.KangLin.ChineseChess.desktop ]; then
        ln -s $INSTALL_PREFIX/share/applications/io.github.KangLin.ChineseChess.desktop /usr/share/applications/io.github.KangLin.ChineseChess.desktop
        chmod a+rx /usr/share/applications/io.github.KangLin.ChineseChess.desktop
    fi
fi
if [ ! -f /usr/share/pixmaps/io.github.KangLin.ChineseChess.png ]; then
    if [ -f $INSTALL_PREFIX/share/icons/hicolor/scalable/apps/io.github.KangLin.ChineseChess.png ]; then
        if [ ! -d /usr/share/pixmaps ]; then
            mkdir -p /usr/share/pixmaps
        fi
        ln -s $INSTALL_PREFIX/share/icons/hicolor/scalable/apps/io.github.KangLin.ChineseChess.png /usr/share/pixmaps/io.github.KangLin.ChineseChess.png
    fi
fi
if [ ! -f /usr/bin/ChineseChess ]; then
    ln -s $INSTALL_PREFIX/bin/ChineseChessApp /usr/bin/ChineseChess
fi

if [ -d $INSTALL_PREFIX/etc ]; then
    chmod -R a+rw $INSTALL_PREFIX/etc
fi

# 卸载前需要做的任务 如：停止任务
%preun
rm -fr /usr/share/applications/io.github.KangLin.ChineseChess.desktop
rm -fr /usr/share/pixmaps/io.github.KangLin.ChineseChess.png
rm -fr /usr/bin/ChineseChess

# 卸载后需要做的任务 如：删除用户，删除/备份业务数据
%postun

# 清除上次编译生成的临时文件
%clean

# 设置文件属性，包含编译文件需要生成的目录、文件以及分配所对应的权限
%files
%dir %{INSTALL_PREFIX}

%{INSTALL_PREFIX}/*

# 修改历史
%changelog
* %{build_time} Kang Lin <kl222@126.com> - %{version}
- Initial RPM package
