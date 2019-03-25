<template>
  <div id="app">
  
<el-menu
  :default-active="activeIndex2"
  class="el-menu-demo"
  mode="horizontal"
  @select="handleSelect"
  background-color="#545c64"
  text-color="#fff"
  active-text-color="#ffd04b"
  style="width: 100%">
  <el-menu-item index="1"><router-link to="/showresult">处理中心</router-link></el-menu-item>
  <el-submenu index="2">
    <template slot="title">我的工作台</template>
    <el-menu-item index="2-1">选项1</el-menu-item>
    <el-menu-item index="2-2">选项2</el-menu-item>
    <el-menu-item index="2-3">选项3</el-menu-item>
    <el-submenu index="2-4">
      <template slot="title">选项4</template>
      <el-menu-item index="2-4-1">选项1</el-menu-item>
      <el-menu-item index="2-4-2">选项2</el-menu-item>
      <el-menu-item index="2-4-3">选项3</el-menu-item>
    </el-submenu>
  </el-submenu>
  <el-menu-item index="3" ><router-link to="/addTrainNumber">处理中心</router-link></el-menu-item>
  <el-menu-item index="4"><a href="baidu.com" target="_blank">订单管理</a></el-menu-item>
</el-menu>

  <el-main><router-view></router-view></el-main>

  <el-footer>Footer</el-footer>

  </div>
</template>

<script>
  export default {
    name: 'ticket-booking',
    data () {
      return {
        activeIndex: '1',
        activeIndex2: '1'
      }
    }
  }
</script>

<style>
  /* CSS */
  body {
    font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
  }
</style>
