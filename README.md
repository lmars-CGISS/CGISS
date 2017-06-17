# CGISS
CGISS是Chinese Geographic information-Storage Specification的简称，是一种地理空间数据交换工具。地理空间数据交换与共享软件是一款工具性软件，其工作目的是以矢量和栅格数据交换标准格式为中心，常见GIS格式以及国内GIS厂商的GIS数据格式之间的相互转换。地理空间数据交换与共享软件采用插件式框架实现多种GIS数据格式的支持，同时也支持通过插件扩展支持更多的GIS数据格式。
## 项目背景
* 标准化是地理空间数据共享和系统集成的重要前提，也是地理信息产业化、社会化的必由之路。地理空间数据内容描述与存 储是最为基础的地理信息共性技术，是地理信息服务高效提供的保障。虽然我国地理信息服务与应用近年来得到飞速的发展，但目前地理空间数据内容模型与存储格式标准还是空白，这阻碍了地理空间信息共享与应用，影响了地理信息产业发展
* 开发支持国内外常用地理空间数据格式与存储标准的数据交换软件，有助于保障国家地理信息安全，促进地理信息产业的发展。
## 项目平台及用户群
* 项目平台为Windows7 以及以上版本32位、64位操作系统
* 地理空间数据交换与共享软件的用户群体为国内各GIS厂商，以及各GIS厂商的使用客户，及GIS软件开发人员以及专业GIS数据处理人员
## 技术支持
地理空间数据交换与共享工具关键技术点考虑如下：
* 开发工具采用Visual Studio 2010
* 工具主框架采用C#语言开发
* 插件接口采用C++接口定义
* 插件运行模块采用VC CLR封装
* 插件可能运行于独立线程，插件本身的实现需要考虑线程安全
## 基本功能
* 将国内各GIS厂商以及ArcGIS的矢量、栅格数据转换为矢量、栅格标准交换格式
* 将矢量、栅格标准交换格式转换成各GIS厂商以及ArcGIS的矢量、栅格格式
* 功能插件的管理功能，功能插件的注册、删除等
* 支持全图漫游，放大缩小，以及批量转换
## 框架
![](https://ooo.0o0.ooo/2017/06/15/5942266f25236.png)

