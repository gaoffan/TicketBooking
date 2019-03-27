<template>
  <el-container class="container">
  <el-header class="header">
     <el-menu router mode="horizontal" default-active="1"
     background-color="#36424F"
     text-color="#fff"
  active-text-color="#707274">
    <el-menu-item index="1" route="/">
      <i class="el-icon-menu"></i>
      <span slot="title">在线订票</span>
    </el-menu-item>
    <el-menu-item index="2" route="/orders">
      <i class="el-icon-document"></i>
      <span slot="title">我的订单</span>
    </el-menu-item>
    <el-menu-item index="3" route="/addTrainNumber">
      <i class="el-icon-setting"></i>
      <span slot="title">管理面板</span>
    </el-menu-item>
  </el-menu>
  </el-header>
    <el-main class="main"><router-view></router-view></el-main>
  </el-container>
</template>

<script>
  export default {
    name: 'ticket-booking',
    data () {
      return {
        activeIndex: '1'
      }
    }
  }
</script>

<style>
  /* CSS */
  body {
    font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
  }

.container {
    position: absolute;
    top: 0;
    bottom: 0;
    width: 100%;
}
.header {
    text-align: center;
    padding: 0;
}
.main {
  padding: 10px;
}
</style>
